QT += qml quick

INCLUDEPATH += $$PWD

SOURCES += \
	$$PWD/osc_sender.cpp \
	$$PWD/osc_receiver.cpp

HEADERS += \
	$$PWD/osc_sender.h \
	$$PWD/osc_receiver.h

exists( $$PWD/oscpack/liboscpack.* ) {
	QMAKE_LIBDIR += $$PWD/oscpack
}

QMAKE_LIBS   += -loscpack

OTHER_FILES = qmldir
