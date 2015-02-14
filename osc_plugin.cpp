#include "osc_plugin.h"
#include "osc_receiver.h"
#include "osc_sender.h"

#include <qqml.h>

void OSCPlugin::registerTypes(const char *uri)
{
    // @uri OSC
    qmlRegisterType<OSCReceiver>(uri, 1, 1, "OSCReceiver");
    qmlRegisterType<OSCSender>(uri, 1, 1, "OSCSender");
}
