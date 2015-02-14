#ifndef OSC_SENDER_H
#define OSC_SENDER_H

#include <QQuickItem>
#include "oscpack/ip/UdpSocket.h"


class OSCSender : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)

public:
    explicit OSCSender(QQuickItem *parent = 0);
    Q_INVOKABLE void send(const QString& address, const QList<QVariant>& param);
    QString getHost() const;
    void setHost(const QString& host);
    int getPort() const;
    void setPort(int port);

signals:
    void error(const QString& msg);
    void hostChanged();
    void portChanged();

private:
    std::string host_;
    int port_;
    UdpTransmitSocket socket_;
};


#endif // OSC_H
