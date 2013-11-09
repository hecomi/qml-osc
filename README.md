qml-osc
==============

Overview
--------
- QML custom element that can handle OSC message.

Libraries
---------
- [oscpack](http://www.rossbencina.com/code/oscpack)

License
-------
- MIT License

Usage
-----
1. Include ```osc.pri``` into your qt project.

```
include(../osc/osc.pri)

folder_01.source = qml/CustomElementsTest
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01
...
```

2. Register custom qml in your ```main.cpp```.

```cpp
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <osc_receiver.h> // add
#include <osc_sender.h>   // add

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<OSCReceiver>("OSC", 1, 0, "OSCReceiver"); // add
    qmlRegisterType<OSCSender>("OSC", 1, 0, "OSCSender");     // add

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/CustomElementsTest/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
```

3. Using custom QML named ```OSCReceiver``` and ```OSCSender``` in your qml files.

```javascript
import QtQuick 2.0
import OSC 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        id: message
        anchors.centerIn: parent
    }
    OSCReceiver {
        port: 3333
        onMessage: {
            message.text = address + ' : ' + msg;
        }
    }
    OSCSender {
        id: osc
        ip: '127.0.0.1'
        port: 3333
    }
    Timer {
        property int cnt: 0
        interval: 1000/60
        running: true
        repeat: true
        onTriggered: {
            osc.send('/Hoge/cnt', ++cnt);
        }
    }
}
```

