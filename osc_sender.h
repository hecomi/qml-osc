#ifndef OSC_SENDER_H
#define OSC_SENDER_H

#include <QQuickItem>
#include "ip/UdpSocket.h"


class OSCSender : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString ip READ getIp WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)

public:
    explicit OSCSender(QQuickItem *parent = 0);
    Q_INVOKABLE void send(const QString& address, const QString& param);
    QString getIp() const;
    void setIp(const QString& ip);
    int getPort() const;
    void setPort(int port);

signals:
    void error(const QString& msg);
    void ipChanged();
    void portChanged();

private:
    std::string ip_;
    int port_;
    UdpTransmitSocket socket_;
};


#endif // OSC_H
