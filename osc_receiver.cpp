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
        QList<QVariant> msg;
        osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        while (arg != m.ArgumentsEnd()) {
            if ((arg)->IsFloat()) {
                msg.append((arg)->AsFloat());
            } else if ((arg)->IsInt32()) {
                msg.append((arg)->AsInt32());
            } else if ((arg)->IsBool()) {
                msg.append((arg)->AsBool());
            } else {
                msg.append((arg)->AsString());
            }
            arg++;
        }
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


void OSCReceiver::onMessage(const QString &address, const QList<QVariant> &msg)
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

