#include "GLDrawerPlugin.h"
#include "GLDrawer.h"

#include <QtPlugin>

GLDrawerPlugin::GLDrawerPlugin(QObject *parent)
  : QObject(parent) {
  initialized = false;
}

void GLDrawerPlugin::initialize(QDesignerFormEditorInterface* core) {
  if (initialized)
    return;
  initialized = true;
}

bool GLDrawerPlugin::isInitialized() const {
  return initialized;
}

QWidget* GLDrawerPlugin::createWidget(QWidget* parent) {
  return new GLDrawer(parent);
}

QString GLDrawerPlugin::name() const {
  return "GLDrawer";
}

QString GLDrawerPlugin::group() const {
  // muuta tama
  return "Display Widgets [Examples]";
}

QIcon GLDrawerPlugin::icon() const {
  return QIcon();
}

QString GLDrawerPlugin::toolTip() const {
  return "OpenGL visualization for Lignum";
}

QString GLDrawerPlugin::whatsThis() const {
  return "Visualization for Lignum";
}

bool GLDrawerPlugin::isContainer() const {
  return false;
}

QString GLDrawerPlugin::domXml() const {
return "<widget class=\"GLDrawer\" name=\"GLDrawer\">\n"
               " <property name=\"geometry\">\n"
               "  <rect>\n"
               "   <x>0</x>\n"
               "   <y>0</y>\n"
               "   <width>500</width>\n"
               "   <height>500</height>\n"
               "  </rect>\n"
               " </property>\n"
               " <property name=\"toolTip\" >\n"
               "  <string>OpenGL visualization for Lignum</string>\n"
               " </property>\n"
               " <property name=\"whatsThis\" >\n"
               "  <string> Visualization for Lignum</string>\n"
               " </property>\n"
               "</widget>\n";
}

QString GLDrawerPlugin::includeFile() const {
  return "GLDrawer.h";
}

Q_EXPORT_PLUGIN2(customwidgetplugin, GLDrawerPlugin)
