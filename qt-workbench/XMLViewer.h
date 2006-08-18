#ifndef XMLVIEWER_H
#define XMLVIEWER_H

#include <QDomDocument>
#include <QHash>
#include <QIcon>
#include <QTreeWidget>
#include <vector>

using namespace std;

class XMLViewer : public QTreeWidget
{
  Q_OBJECT
  
public:

  XMLViewer(QWidget *parent = 0);
  
  bool addTree(QString fileName);
  void addTree(QDomDocument document, QString fileName);

signals:
  
  void sceneObjectsSelected(QList<int>);

private slots:
 
  void selectSceneObjects(); 

private:
  void parseTreeElement(const QDomElement &element, QString fileName,
			  QTreeWidgetItem *parentItem = 0);
  void parseAttributeElement(const QDomElement &element,
			     QTreeWidgetItem *parentItem);
  void parseAxisElement(const QDomElement &element,
			QTreeWidgetItem *parentItem);
  void parseTreeSegmentElement(const QDomElement &element,
			       QTreeWidgetItem *parentItem);
  void parseBranchingPointElement(const QDomElement &element,
				  QTreeWidgetItem *parentItem);
  void parseBudElement(const QDomElement &element,
		       QTreeWidgetItem *parentItem);
  void parseBroadLeafElement(const QDomElement &element,
		       QTreeWidgetItem *parentItem);
  

  QTreeWidgetItem *createItem(const QDomElement &element,
			      QTreeWidgetItem *parentItem = 0);

  vector<QDomDocument> documents;
  QHash<QTreeWidgetItem *, QDomDocument> domDocumentForItem;
  QHash<QTreeWidgetItem *, int> sceneObjectIndexForItem;
  //QTreeWidgetItem *rootItem;
  
  
};

#endif
