#include <QtGui>

#include "XMLViewer.h"
#include <iostream>

using namespace cxxadt;
using namespace std;

XMLViewer::XMLViewer(QWidget *parent)
  : QTreeWidget(parent), use_tracking(false)
{

  QStringList labels;
  labels << "Component/Attribute" << "Value";
  
  header()->setResizeMode(QHeaderView::Stretch);
  setHeaderLabels(labels);
 
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  
  connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(selectSceneObjects()));
  connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(setFocus()));
}

bool XMLViewer::addTree(QString fileName) 
{
  QDomDocument domDocument;
  QString errorStr;
  int errorLine;
  int errorColumn;
  
  for(int i = 0; i < files.size(); i++)
    if(*files[i] == fileName) {
      emit textOutput(QString("File %1 has already been loaded.").arg(fileName));
      return false;	
    }	
  
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
  /*  for(int i = 0; i < files.size(); i++)
    if(*files[i] == fileName) {
      emit statusText(QString("File %1 has already been loaded.").arg(fileName), 3000);
      return false;	
      }*/	 
  
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
  QTreeWidgetItem *item = createItem(element, fileName , parentItem);
  rootItemForFileName.insert(*fileName, item);		
	
  QString elementName = element.tagName();
  item->setText(0, elementName + QString("%1").arg(files.size()));
  item->setCheckState(0, Qt::Checked);
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
		 Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

  QTreeWidgetItem *fileNameItem = new QTreeWidgetItem(item);
  fileNameItem->setText(0, QString("File name"));
  fileNameItem->setText(1, *fileName);
  fileNameForItem.insert(fileNameItem, fileName);
  
  setItemExpanded(item, false);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "TreeAttributes") {
      parseAttributeElement(child, fileName, item);
    }
    else if(child.tagName() == "TreeParameters") {
      parseAttributeElement(child, fileName, item);
    }
    else if(child.tagName() == "TreeFunctions") {
      parseAttributeElement(child, fileName, item);
    }
    else if(child.tagName() == "Axis") {
      parseAxisElement(child, fileName, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseAttributeElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, fileName, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);
  
  QDomElement child = element.firstChildElement();
  while(!child.isNull()) {
    QTreeWidgetItem *childItem = createItem(child, fileName, item);
    QString childName = child.tagName();
    childItem->setText(0, childName);
    childItem->setText(1, child.text());
    
    child = child.nextSiblingElement();
  }

}

void XMLViewer::parseAxisElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, fileName, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "AxisAttributes") {
      parseAttributeElement(child, fileName, item);
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
  QTreeWidgetItem *item = createItem(element, fileName, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty())
    sceneObjectIndexForItem.value(*fileName)->insert(item, o_index.toInt());
  //  fileNameForItem.insert(item, fileName);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "TreeSegmentAttributes") {
      parseAttributeElement(child, fileName, item);
    }
    else if(child.tagName() == "BroadLeaf") {
      parseBroadLeafElement(child, fileName, item);
    }

    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBranchingPointElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, fileName, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "BranchingPointAttributes") {
      parseAttributeElement(child, fileName, item);
    }
    else if(child.tagName() == "Axis") {
      parseAxisElement(child, fileName, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBudElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, fileName, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty()) {
    sceneObjectIndexForItem.value(*fileName)->insert(item, o_index.toInt());
  }
  //  fileNameForItem.insert(item, fileName);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "BudAttributes") {
      parseAttributeElement(child, fileName, item);
    }
    child = child.nextSiblingElement();
  }
}

void XMLViewer::parseBroadLeafElement(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item = createItem(element, fileName, parentItem);
  
  QString elementName = element.tagName();
  item->setText(0, elementName);
  
  setItemExpanded(item, false);

  QString o_index = element.attribute("ObjectIndex");
  if(!o_index.isEmpty())
    sceneObjectIndexForItem.value(*fileName)->insert(item, o_index.toInt());
  //fileNameForItem.insert(item, fileName);

  QDomElement child = element.firstChildElement();
  while (!child.isNull()) {
    if(child.tagName() == "BroadLeafAttributes") {
      parseAttributeElement(child, fileName, item);
    }
    child = child.nextSiblingElement();
  }
}

QTreeWidgetItem *XMLViewer::createItem(const QDomElement &element, QString *fileName, QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item;
  if (parentItem) {
    item = new QTreeWidgetItem(parentItem);
  }
  
  else {
    item = new QTreeWidgetItem(this);
  }
  fileNameForItem.insert(item, fileName);

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
  if(fileList.size() >= 1)
    focusedFile = fileList[fileList.size()-1];
  emit updateVisualization(fileList);	
}

void XMLViewer::removeSelected() {
  //QList<QTreeWidgetItem*> items = selectedItems();
  QList<QString *> filesToBeRemoved;
  /*  for(int i = 0; i < items.size(); i++) {
    if(fileNameForItem.contains(items[i])) {
      QString *fileName = fileNameForItem.value(items[i]);
      if(!filesToBeRemoved.contains(fileName))
	filesToBeRemoved.push_back(fileName);
    }
    }*/
  for(int i = 0; i < files.size(); i++) {
    if(rootItemForFileName.contains(*files[i])) {
      if(rootItemForFileName.value(*files[i])->checkState(0) == Qt::Checked)
	filesToBeRemoved.push_back(files[i]);
    }
  }
  

  for(int i = 0; i < filesToBeRemoved.size(); i++) {
    if(sceneObjectIndexForItem.contains(*filesToBeRemoved[i])) {
      //      sceneObjectIndexForItem.value(*filesToBeRemoved[i])->clear();
      delete sceneObjectIndexForItem.value(*filesToBeRemoved[i]);
      sceneObjectIndexForItem.remove(*filesToBeRemoved[i]);
    }

    if(rootItemForFileName.contains(*filesToBeRemoved[i])) {
      QTreeWidgetItem *root = rootItemForFileName.value(*filesToBeRemoved[i]);
      rootItemForFileName.remove(*filesToBeRemoved[i]);
      deleteItem(root);
    }

    for(int j = 0; j < files.size(); j++) {
      if(files[j] == filesToBeRemoved[i]) {
	files.removeAt(j);
	delete filesToBeRemoved[i];
	break;
      }	
    }
  }

}

// Deletes a item and it's children recursevily
// from the XML viewer. 
void XMLViewer::deleteItem(QTreeWidgetItem *item) {
  while(item->childCount() > 0) {
    deleteItem(item->takeChild(0));
  }

  // Delete 
  if(fileNameForItem.contains(item))
    fileNameForItem.remove(item);
  delete item;
}

// Sets the focus of the visualization to the object
// which is last in the list of items currently selected
// in the XML viewer.
void XMLViewer::setFocus() {
  if(!use_tracking)
    return;
  QList<QTreeWidgetItem *> items = selectedItems();
  if(items.size() < 1)
    return;

  QTreeWidgetItem *root = items[items.size()-1];
  QTreeWidgetItem *child;

  // If the last item is a root item of a tree.
  if(root->parent() == NULL) {
    for(int i = 0; i < root->childCount();i++) {
      child = root->child(i);
      if(child->text(0) == QString("TreeAttributes")) {
	Point point;
	PositionVector direction;
	double height;
	double x, y, z;
	QTreeWidgetItem *child2;
	for(int j = 0; j < child->childCount(); j++) {
	  child2 = child->child(j);
	  if(child2->text(0) == QString("point")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	  point = Point(x, y, z);
	  }
	  else if(child2->text(0) == QString("direction")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	    direction = PositionVector(x, y, z);
	  }
	  else if(child2->text(0) == QString("LGAH")) {
	    QString data = child2->text(1);
	    height = data.toDouble();
	    emit setFocus(point, direction, height);
	    return;
	  }
	} 
      }
    }
  }
  else if(root->text(0) == "Axis") {
    for(int i = 0; i < root->childCount();i++) {
      child = root->child(i);
      if(child->text(0) == QString("AxisAttributes")) {
	Point point;
	PositionVector direction;
	double height;
	double x, y, z;
	QTreeWidgetItem *child2;
	for(int j = 0; j < child->childCount(); j++) {
	  child2 = child->child(j);
	  if(child2->text(0) == QString("point")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	  point = Point(x, y, z);
	  }
	  else if(child2->text(0) == QString("direction")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	    direction = PositionVector(x, y, z);
	  }
	  else if(child2->text(0) == QString("LGAL")) {
	    QString data = child2->text(1);
	    height = data.toDouble();
	    emit setFocus(point, direction, height);
	    return;
	  }
	} 
      }
    }
  }
  else if(root->text(0) == "TreeSegment") {
    for(int i = 0; i < root->childCount();i++) {
      child = root->child(i);
      if(child->text(0) == QString("TreeSegmentAttributes")) {
	Point point;
	PositionVector direction;
	double height;
	double x, y, z;
	QTreeWidgetItem *child2;
	for(int j = 0; j < child->childCount(); j++) {
	  child2 = child->child(j);
	  if(child2->text(0) == QString("point")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	  point = Point(x, y, z);
	  }
	  else if(child2->text(0) == QString("direction")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	    direction = PositionVector(x, y, z);
	  }
	  else if(child2->text(0) == QString("LGAL")) {
	    QString data = child2->text(1);
	    height = data.toDouble();
	    emit setFocus(point, direction, height);
	    return;
	  }
	} 
      }
    }
  }
  
  else if(root->text(0) == "Bud") {
    for(int i = 0; i < root->childCount();i++) {
      child = root->child(i);
      if(child->text(0) == QString("BudAttributes")) {
	Point point;
	PositionVector direction;
	double height;
	double x, y, z;
	QTreeWidgetItem *child2;
	for(int j = 0; j < child->childCount(); j++) {
	  child2 = child->child(j);
	  if(child2->text(0) == QString("point")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	  point = Point(x, y, z);
	  }
	  else if(child2->text(0) == QString("direction")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	    direction = PositionVector(x, y, z);
	    emit setFocus(point, direction, 0);
	    return;
	  }
	} 
      }
    }
  }

  else if(root->text(0) == "BranchingPoint") {
    for(int i = 0; i < root->childCount();i++) {
      child = root->child(i);
      if(child->text(0) == QString("BranchingPointAttributes")) {
	Point point;
	PositionVector direction;
	double height;
	double x, y, z;
	QTreeWidgetItem *child2;
	for(int j = 0; j < child->childCount(); j++) {
	  child2 = child->child(j);
	  if(child2->text(0) == QString("point")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	  point = Point(x, y, z);
	  }
	  else if(child2->text(0) == QString("direction")) {
	    QString data = child2->text(1);
	    x = data.section(' ', 0, 0).toDouble();
	    y = data.section(' ', 1, 1).toDouble();
	    z = data.section(' ', 2, 2).toDouble();
	    direction = PositionVector(x, y, z);
	    emit setFocus(point, direction, 0);
	    return;
	  }
	} 
      }
    }
  }
}

void XMLViewer::useTracking(bool use) {
  use_tracking = use;
}
