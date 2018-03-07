CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(SpreadSheetWidgetPlugin)
TEMPLATE    = lib

HEADERS     = SpreadSheetWidgetPlugin.h
SOURCES     = SpreadSheetWidgetPlugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L.

QT += designer


target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(SpreadSheetWidget.pri)
