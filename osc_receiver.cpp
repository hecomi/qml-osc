#include <iostream>
#include "osc_receiver.h"


// ==================================== MyPacketListner =============================================


MyPacketListener::MyPacketListener(MyPacketListenerWorker* parent)
    : osc::OscPacketListener(), parent_(parent)
{
}


void MyPacketListener::ProcessMessage(const osc::ReceivedMessage &m, const IpEndpointName &remoteEndpoint)
{
    (void) remoteEndpoint;

    try {
        auto args = m.ArgumentStream();
        const char* msg;
        args >> msg >> osc::EndMessage;
        emit parent_->message(m.AddressPattern(), msg);
    } catch (const osc::Exception& e) {
        std::cerr << "[OSCReceiver] Error while parsing process message." << std::endl;
        std::cerr << m.AddressPattern() << ": " << e.what() << std::endl;
    }
}


// ==================================== MyPacketListnerWorker =============================================


MyPacketListenerWorker::MyPacketListenerWorker(int port)
    : QObject(NULL), listener_(this),
      socket_(IpEndpointName(port), &listener_)
{
}


void MyPacketListenerWorker::start()
{
    socket_.Run();
}


// ==================================== OSCReceiver =============================================


OSCReceiver::OSCReceiver(QQuickItem *parent)
    : QQuickItem(parent), port_(3333), isRunning_(false)
{
}


OSCReceiver::~OSCReceiver()
{
    workerThread_.exit();
}


void OSCReceiver::run()
{
    if (isRunning_) return;
    isRunning_ = true;

    try {
        worker_ = new MyPacketListenerWorker(port_);
        worker_->moveToThread(&workerThread_);
        connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);
        connect(worker_, &MyPacketListenerWorker::message, this, &OSCReceiver::onMessage);
        connect(this, &OSCReceiver::start, worker_, &MyPacketListenerWorker::start);
        workerThread_.start();
        emit start();
    } catch(const std::exception& e) {
        emit error(e.what());
        isRunning_ = false;
    }
}


void OSCReceiver::onMessage(const QString &address, const QString &msg)
{
    emit message(address, msg);
}


void OSCReceiver::setPort(int port)
{
    // if (isRunning_) return;

    port_ = port;
    run();
    emit portChanged();
}


int OSCReceiver::getPort() const
{
    return port_;
}

