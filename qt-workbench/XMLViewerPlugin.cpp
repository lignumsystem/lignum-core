#include "XMLViewerPlugin.h"
#include "XMLViewer.h"

#include <QtPlugin>

XMLViewerPlugin::XMLViewerPlugin(QObject *parent)
  : QObject(parent) {
  initialized = false;
}

void XMLViewerPlugin::initialize(QDesignerFormEditorInterface* core) {
  if (initialized)
    return;
  initialized = true;
}

bool XMLViewerPlugin::isInitialized() const {
  return initialized;
}

QWidget* XMLViewerPlugin::createWidget(QWidget* parent) {
  return new XMLViewer(parent);
}

QString XMLViewerPlugin::name() const {
  return "XMLViewer";
}

QString XMLViewerPlugin::group() const {
  return "Display Widgets [Examples]";
}

QIcon XMLViewerPlugin::icon() const {
  return QIcon();
}

QString XMLViewerPlugin::toolTip() const {
  return "XML Viewer for Lignum";
}

QString XMLViewerPlugin::whatsThis() const {
  return "XML Viewer for Lignum";
}

bool XMLViewerPlugin::isContainer() const {
  return false;
}

QString XMLViewerPlugin::domXml() const {
return "<widget class=\"XMLViewer\" name=\"XMLViewer\">\n"
               " <property name=\"geometry\">\n"
               "  <rect>\n"
               "   <x>0</x>\n"
               "   <y>0</y>\n"
               "   <width>300</width>\n"
               "   <height>300</height>\n"
               "  </rect>\n"
               " </property>\n"
               " <property name=\"toolTip\" >\n"
               "  <string>Function painter for Lignum</string>\n"
               " </property>\n"
               " <property name=\"whatsThis\" >\n"
               "  <string> Function painter for Lignum</string>\n"
               " </property>\n"
               "</widget>\n";
}

QString XMLViewerPlugin::includeFile() const {
  return "XMLViewer.h";
}

Q_EXPORT_PLUGIN2(customwidgetplugin, XMLViewerPlugin)
