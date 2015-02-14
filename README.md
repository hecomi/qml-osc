# qml-osc
[Qt Modeling Language](http://en.wikipedia.org/wiki/QML) extension for sending and receiving [Open Sound Control](http://en.wikipedia.org/wiki/Open_Sound_Control) messages.

You can use qml-osc with ["qml runtime"](http://www.ics.com/blog/whole-shebang-running-qml-files-directly) or your [custom Qt project](#qt-example).

## Usage
```qml
import OSC 1.1
```

#### OSCSender
```qml
OSCSender {
    id: osc
    host: "localhost"
    port: 3333
}

Button {
    onClicked: osc.send("/foo/bar", ["hello", 42, 3.14, true])
}
```

#### OSCReceiver
```qml
OSCReceiver {
    port: 3333
    onMessage: {
        console.log(address, msg)
    }
}
```

#### Full Example
```qml
import QtQuick 2.4
import QtQuick.Controls 1.3
import OSC 1.1

ApplicationWindow {
    title: "Test OSC"
    width: 260
    height: 160
    visible: true

    OSCReceiver {
        port: 3333
        onMessage: {
            output.text = "<b>" + address + "</b><br>";
            for (var i = 0; i < msg.length; i++) {
                output.text += msg[i] + " <i>" + typeof msg[i] + "</i><br>";
            }
        }
    }

    OSCSender {
        id: osc
        host: "localhost"
        port: 3333
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: "transparent"

        Text {
            id: output
        }

        Button {
            text: "send"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: osc.send("/foo/bar", ["hello", 42, 3.14, true])
        }
    }
}
```

##### Output
<pre>
<b>/foo/bar</b>
hello <i>string</i>
42 <i>number</i>
3.140000104904175 <i>number</i>
true <i>boolean</i>
</pre>

## Build as shared library

### Dependecies
- [oscpack](https://code.google.com/p/oscpack/)

### Linux
```sh
qmake .
make PREFIX=/usr/local
```

## Install systemwide

### Linux
```sh
install -Dm755 libOSC.so /usr/local/lib/qt/qml/OSC/libOSC.so
install -Dm744 qmldir /usr/local/lib/qt/qml/OSC/qmldir
```

## Custom Qt project example <a name="qt-example"></a>

Include ```osc.pri``` into your qt project.

```
include(../osc/osc.pri)

folder_01.source = qml/CustomElementsTest
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01
...
```

Register custom qml in your ```main.cpp```.

```cpp
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <osc_receiver.h> // add
#include <osc_sender.h>   // add

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<OSCReceiver>("OSC", 1, 1, "OSCReceiver"); // add
    qmlRegisterType<OSCSender>("OSC", 1, 1, "OSCSender");     // add

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/CustomElementsTest/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
```

## License
The MIT License (MIT)

Copyright (c) 2013 hecomi

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

