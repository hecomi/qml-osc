#include "osc_sender.h"
#include "oscpack/osc/OscOutboundPacketStream.h"


namespace {
    const size_t OUTPUT_BUFFER_SIZE = 8192;
}


OSCSender::OSCSender(QQuickItem *parent) :
    QQuickItem(parent), host_("127.0.0.1"), port_(3333),
    socket_(IpEndpointName(host_.c_str(), port_))
{
}


void OSCSender::setHost(const QString &host)
{
    try {
        host_ = host.toStdString();
        socket_ .Connect(IpEndpointName(host_.c_str(), port_));
        emit hostChanged();
    } catch (const std::exception& e) {
        emit error(e.what());
    }
}


QString OSCSender::getHost() const
{
    return host_.c_str();
}

void OSCSender::setPort(int port)
{
    try {
        port_ = port;
        socket_.Connect(IpEndpointName(host_.c_str(), port_));
        emit portChanged();
    } catch (const std::exception& e) {
        emit error(e.what());
    }
}


int OSCSender::getPort() const
{
    return port_;
}


void OSCSender::send(const QString &address, const QList<QVariant> &param)
{
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

    p << osc::BeginBundleImmediate
      << osc::BeginMessage(address.toStdString().c_str());
    for (int i = 0; i < param.size(); ++i) {
        switch (param.at(i).type()) {
            case QVariant::Double:
                p << param.at(i).toFloat();
                break;
            case QVariant::Int:
                p << param.at(i).toInt();
                break;
            case QVariant::Bool:
                p << param.at(i).toBool();
                break;
            default:
                p << param.at(i).toString().toStdString().c_str();
        }
    }
    p << osc::EndMessage;

    socket_.Send(p.Data(), p.Size());
}

