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
  

  return addTree(domDocument, fileName);
    
}

bool XMLViewer::addTree(QDomDocument document, QString fileName)
{
  //documents.push_back(document);
  for(int i = 0; i < files.size(); i++)
	 if(*files[i] == fileName)
	    return false;		 
  
  QString* file_name = new QString(fileName);
  files.push_back(file_name);
  QDomElement root = document.documentElement();

  sceneObjectIndexForItem.insert(fileName, new QHash<QTreeWidgetItem *, int>());	
	if(root.tagName() == QString("Tree"))	
  parseTreeElement(root, file_name);
  
  return true;			
}

void XMLViewer::parseTreeElement(const QDomElement &element, QString* fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  rootItemForFileName.insert(*fileName, item);		
	
  QString elementName = element.tagName();
  item->setText(0, elementName + QString("%1").arg(files.size()));
  
  item->setCheckState(0, Qt::Checked);
	
  QTreeWidgetItem *fileNameItem = new QTreeWidgetItem(item);
  fileNameItem->setText(0, QString("File name"));
  fileNameItem->setText(1, *fileName);
  
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
      parseAxisElement(child, fileName, item);
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
    QTreeWidgetItem *childItem = createItem(child, item);
    QString childName = child.tagName();
    childItem->setText(0, childName);
    childItem->setText(1, child.text());
    
    child = child.nextSiblingElement();
  }

}

void XMLViewer::parseAxisElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
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
      parseTreeSegmentElement(child, fileName, item);
    }
    else if(child.tagName() == "BranchingPoint") {
      parseBranchingPointElement(child, fileName, item);
    }
    else if(child.tagName() == "Bud") {
      parseBudElement(child, fileName, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseTreeSegmentElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty())
    sceneObjectIndexForItem.value(*fileName)->insert(item, o_index.toInt());
  fileNameForItem.insert(item, fileName);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "TreeSegmentAttributes") {
      parseAttributeElement(child, item);
    }
    else if(child.tagName() == "BroadLeaf") {
      parseBroadLeafElement(child, fileName, item);
    }

    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBranchingPointElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
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
      parseAxisElement(child, fileName, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBudElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty()) {
    sceneObjectIndexForItem.value(*fileName)->insert(item, o_index.toInt());
  }
  fileNameForItem.insert(item, fileName);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "BudAttributes") {
      parseAttributeElement(child, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBroadLeafElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty())
    sceneObjectIndexForItem.value(*fileName)->insert(item, o_index.toInt());
  fileNameForItem.insert(item, fileName);

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
  QHash<QString, QList<int> > selectedObjects;
  QMultiHash<QString, int> objects;
  QSet<QString> fileNames;
  for(int i = 0; i < items.size(); i++) {
    if(fileNameForItem.contains(items[i])) {
     QString fileName = *fileNameForItem.value(items[i]);		
     if(sceneObjectIndexForItem.value(fileName)->contains(items[i])) {
 
      if(!fileNames.contains(fileName))
	   fileNames.insert(fileName);
	  objects.insert(*fileNameForItem.value(items[i]), sceneObjectIndexForItem.value(fileName)->value(items[i]));
	//cout << sceneObjectIndexForItem.value(items[i]) << endl;
      }
    }
  }

  QSetIterator<QString> i(fileNames);
  while(i.hasNext()) {
    QString file = i.next();
    selectedObjects.insert(file, objects.values(file)); 
  }
  emit sceneObjectsSelected(selectedObjects);
}

void XMLViewer::sendVisualizationUpdate() {
  QList<QString> fileList;
  for(int i = 0; i < files.size(); i++) {
	  if(rootItemForFileName.contains(*files[i])) 
    	  if(rootItemForFileName.value(*files[i])->checkState(0) == Qt::Checked)
             fileList.push_back(*files[i]);		  
  }
  emit updateVisualization(fileList);	
}
