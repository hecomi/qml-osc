include(osc.pri)

TEMPLATE = lib
TARGET = OSC
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = OSC

# Input
SOURCES += \
	osc_plugin.cpp

HEADERS += \
	osc_plugin.h


!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
	copy_qmldir.target = $$OUT_PWD/qmldir
	copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
	copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
	QMAKE_EXTRA_TARGETS += copy_qmldir
	PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
	installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
	qmldir.path = $$installPath
	target.path = $$installPath
	INSTALLS += target qmldir
}

