QT += qml quick

INCLUDEPATH += $$PWD

SOURCES += \
	$$PWD/osc_sender.cpp \
	$$PWD/osc_receiver.cpp

HEADERS += \
	$$PWD/osc_sender.h \
	$$PWD/osc_receiver.h

QMAKE_INCDIR += $$PWD/include
QMAKE_LIBDIR += $$PWD/lib
QMAKE_LIBS   += -loscpack

OTHER_FILES = qmldir
