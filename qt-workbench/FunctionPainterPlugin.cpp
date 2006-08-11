#include "FunctionPainterPlugin.h"
#include "FunctionPainter.h"

#include <QtPlugin>

FunctionPainterPlugin::FunctionPainterPlugin(QObject *parent)
  : QObject(parent) {
  initialized = false;
}

void FunctionPainterPlugin::initialize(QDesignerFormEditorInterface* core) {
  if (initialized)
    return;
  initialized = true;
}

bool FunctionPainterPlugin::isInitialized() const {
  return initialized;
}

QWidget* FunctionPainterPlugin::createWidget(QWidget* parent) {
  return new FunctionPainter(parent);
}

QString FunctionPainterPlugin::name() const {
  return "FunctionPainter";
}

QString FunctionPainterPlugin::group() const {
  // muuta tama
  return "Display Widgets [Examples]";
}

QIcon FunctionPainterPlugin::icon() const {
  return QIcon();
}

QString FunctionPainterPlugin::toolTip() const {
  return "Function painter for Lignum";
}

QString FunctionPainterPlugin::whatsThis() const {
  return "Function painter for Lignum";
}

bool FunctionPainterPlugin::isContainer() const {
  return false;
}

QString FunctionPainterPlugin::domXml() const {
return "<widget class=\"FunctionPainter\" name=\"FunctionPainter\">\n"
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

QString FunctionPainterPlugin::includeFile() const {
  return "FunctionPainter.h";
}

Q_EXPORT_PLUGIN2(customwidgetplugin, FunctionPainterPlugin)
