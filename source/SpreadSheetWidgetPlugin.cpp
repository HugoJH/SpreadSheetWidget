#include "SpreadSheetWidget.h"
#include "SpreadSheetWidgetPlugin.h"

#include <QtPlugin>

SpreadSheetWidgetPlugin::SpreadSheetWidgetPlugin(QObject *parent)
   : QObject(parent)
{
   m_initialized = false;
}

void SpreadSheetWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
   if (m_initialized)
      return;

   // Add extension registrations, etc. here

   m_initialized = true;
}

bool SpreadSheetWidgetPlugin::isInitialized() const
{
   return m_initialized;
}

QWidget *SpreadSheetWidgetPlugin::createWidget(QWidget *parent)
{
   return new SpreadSheetWidget(parent);
}

QString SpreadSheetWidgetPlugin::name() const
{
   return QLatin1String("SpreadSheetWidget");
}

QString SpreadSheetWidgetPlugin::group() const
{
   return QLatin1String("");
}

QIcon SpreadSheetWidgetPlugin::icon() const
{
   return QIcon();
}

QString SpreadSheetWidgetPlugin::toolTip() const
{
   return QLatin1String("");
}

QString SpreadSheetWidgetPlugin::whatsThis() const
{
   return QLatin1String("SpreadSheet-like Widget");
}

bool SpreadSheetWidgetPlugin::isContainer() const
{
   return false;
}

QString SpreadSheetWidgetPlugin::domXml() const
{
   return QLatin1String("<widget class=\"SpreadSheetWidget\" name=\"spreadSheetWidget\">\n</widget>\n");
}

QString SpreadSheetWidgetPlugin::includeFile() const
{
   return QLatin1String("SpreadSheetWidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(SpreadSheetWidgetPlugin, SpreadSheetWidgetPlugin)
#endif // QT_VERSION < 0x050000
