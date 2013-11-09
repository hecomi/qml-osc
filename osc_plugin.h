#ifndef OSC_PLUGIN_H
#define OSC_PLUGIN_H

#include <QQmlExtensionPlugin>

class OSCPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // OSC_PLUGIN_H

