#ifndef OSC_RECEIVER_H
#define OSC_RECEIVER_H

#include <QQuickItem>
#include <QThread>
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"


class MyPacketListenerWorker;


// Listener for Key events on other PC
class MyPacketListener : public osc::OscPacketListener
{
public:
    MyPacketListener(MyPacketListenerWorker* parent);

private:
    void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
    MyPacketListenerWorker* parent_;
};


// Worker
class MyPacketListenerWorker : public QObject
{
Q_OBJECT

public:
    MyPacketListenerWorker(int port);

public slots:
    void start();

signals:
    void message(const QString& address, const QString& msg);

private:
    MyPacketListener listener_;
    UdpListeningReceiveSocket socket_;
};


// Class for Exporting C++ functions to QML
class OSCReceiver : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool isRunning MEMBER isRunning_);

public:
    explicit OSCReceiver(QQuickItem *parent = 0);
    ~OSCReceiver();

    int getPort() const;
    void setPort(int port);

    Q_INVOKABLE void run();

public slots:
    void onMessage(const QString& address, const QString& msg);

signals:
    void message(const QString& address, const QString& msg);
    void error(const QString& msg);
    void start();
    void portChanged();

private:
    int port_;
    bool isRunning_;
    QThread workerThread_;
    MyPacketListenerWorker* worker_;
};


#endif // OSC_RECEIVER_H
