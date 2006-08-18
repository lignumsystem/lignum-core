#include <QtGui>

#include "XMLViewer.h"
#include <iostream>

using namespace std;

XMLViewer::XMLViewer(QWidget *parent)
  : QTreeWidget(parent)
{

  QStringList labels;
  labels << "Component/Attribute" << "Value";
  
  header()->setResizeMode(QHeaderView::Stretch);
  setHeaderLabels(labels);
 
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  
  //rootItem = new QTreeWidgetItem(this);
  //rootItem->setText(0, QString("Trees"));

  connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(selectSceneObjects()));
}

bool XMLViewer::addTree(QString fileName) 
{
  QDomDocument domDocument;
  QString errorStr;
  int errorLine;
  int errorColumn;
  
  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("arks"),
			 tr("Cannot read file %1:\n%2.")
                                 .arg(fileName)
			 .arg(file.errorString()));
    return false;
  }
  

  if (!domDocument.setContent(&file, true, &errorStr, &errorLine,
			      &errorColumn)) {
    QMessageBox::information(window(), tr("XML Viewer"),
			     tr("Parse error at line %1, column %2:\n%3")
			     .arg(errorLine)
			     .arg(errorColumn)
			     .arg(errorStr));
    return false;
  }
  addTree(domDocument, fileName);
  return true;  
}

void XMLViewer::addTree(QDomDocument document, QString fileName)
{
  documents.push_back(document);

  QDomElement root = document.documentElement();

  if(root.tagName() == QString("Tree"))
    parseTreeElement(root, fileName);

}

void XMLViewer::parseTreeElement(const QDomElement &element, QString fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName + QString("%1").arg(documents.size()));
  
  QTreeWidgetItem *fileNameItem = new QTreeWidgetItem(item);
  fileNameItem->setText(0, QString("File name"));
  fileNameItem->setText(1, fileName);
  
  setItemExpanded(item, false);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "TreeAttributes") {
      parseAttributeElement(child, item);
    }
    else if(child.tagName() == "TreeParameters") {
      parseAttributeElement(child, item);
    }
    else if(child.tagName() == "TreeFunctions") {
      parseAttributeElement(child, item);
    }
    else if(child.tagName() == "Axis") {
      parseAxisElement(child, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseAttributeElement(const QDomElement &element, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);
  
  QDomElement child = element.firstChildElement();
  while(!child.isNull()) {
    if(child.tagName() == "BroadLeaf") {
      parseBroadLeafElement(child, item);
    }
    else {
      QTreeWidgetItem *childItem = createItem(child, item);
      QString childName = child.tagName();
      childItem->setText(0, childName);
      childItem->setText(1, child.text());
    }
    child = child.nextSiblingElement();
  }

}

void XMLViewer::parseAxisElement(const QDomElement &element, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "AxisAttributes") {
      parseAttributeElement(child, item);
    }
    else if(child.tagName() == "TreeSegment") {
      parseTreeSegmentElement(child, item);
    }
    else if(child.tagName() == "BranchingPoint") {
      parseBranchingPointElement(child, item);
    }
    else if(child.tagName() == "Bud") {
      parseBudElement(child, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseTreeSegmentElement(const QDomElement &element, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty())
    sceneObjectIndexForItem.insert(item, o_index.toInt());

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "TreeSegmentAttributes") {
      parseAttributeElement(child, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBranchingPointElement(const QDomElement &element, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "BranchingPointAttributes") {
      parseAttributeElement(child, item);
    }
    else if(child.tagName() == "Axis") {
      parseAxisElement(child, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBudElement(const QDomElement &element, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty())
    sceneObjectIndexForItem.insert(item, o_index.toInt());

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "BudAttributes") {
      parseAttributeElement(child, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBroadLeafElement(const QDomElement &element, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty())
    sceneObjectIndexForItem.insert(item, o_index.toInt());

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "BroadLeafAttributes") {
      parseAttributeElement(child, item);
    }
    child = child.nextSiblingElement();
  }
}

QTreeWidgetItem *XMLViewer::createItem(const QDomElement &element, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item;
  if (parentItem) {
    item = new QTreeWidgetItem(parentItem);
  }
  
  else {
    item = new QTreeWidgetItem(this);
  }
  // domElementForItem.insert(item, element);
  return item;
}

void XMLViewer::selectSceneObjects()
{
  QList<QTreeWidgetItem*> items = selectedItems();
  QList<int> selectedObjects;
  for(int i = 0; i < items.size(); i++) {
    if(sceneObjectIndexForItem.contains(items[i])) {
      selectedObjects.push_back(sceneObjectIndexForItem.value(items[i]));
      //cout << sceneObjectIndexForItem.value(items[i]) << endl;
    }
  }
  emit sceneObjectsSelected(selectedObjects);
}
