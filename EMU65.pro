# Add more folders to ship with the application, here
folder_01.source = qml/EMU65
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

CONFIG += c++14
DEFINES += DEBUG

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

DESTDIR = $$PWD

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/debug/aiminspector.cpp \
    src/aim65.cpp \
    src/iocomponents/channel.cpp \
    src/iocomponents/cpuchannel.cpp \
    src/iocomponents/iobus.cpp \
    src/iocomponents/iochannel.cpp \
    src/iocomponents/iocomponent.cpp \
    src/iocomponents/iocomponentirq.cpp \
    src/iocomponents/leddisplay.cpp \
    src/iocomponents/keyboard.cpp \
    src/iocomponents/printer.cpp \
    src/iocomponents/audiotape.cpp \
    src/iocomponents/unmappedmemoryexception.cpp \
    src/M6502/cpu.cpp \
    src/M6502/M6502.cpp \
    src/M6502/cpuqthread.cpp \
    src/ui/uiproxy.cpp \
    src/ui/uiproxycollection.cpp \
    src/ui/keyboardqtproxy.cpp \
    src/ui/leddisplayqtproxy.cpp \
    src/ui/aim65proxy.cpp \
    src/filehandling/imageloader.cpp \
    src/filehandling/fileprinter.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += include/aim65.h \
    include/globals.h \
    include/debug/aiminspector.h \
    include/iocomponents/channel.h \
    include/iocomponents/cpuchannel.h \
    include/iocomponents/iobus.h \
    include/iocomponents/iochannel.h \
    include/iocomponents/iocomponent.h \
    include/iocomponents/iocomponentirq.h \
    include/iocomponents/leddisplay.h \
    include/iocomponents/keyboard.h \
    include/iocomponents/printer.h \
    include/iocomponents/audiotape.h \
    include/iocomponents/unmappedmemoryexception.h \
    include/M6502/cpu.h \
    include/M6502/M6502.h \
    include/M6502/cpuqthread.h \
    include/ui/uiproxy.h \
    include/ui/uiproxycollection.h \
    include/ui/leddisplayqtproxy.h \
    include/ui/aim65proxy.h \
    include/ui/keyboardqtproxy.h \
    include/filehandling/imageloader.h \
    include/filehandling/fileprinter.h

TARGET = EMU65

OTHER_FILES += \
    EMU65/qml/EMU65/main.qml
