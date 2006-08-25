#ifndef XMLVIEWER_H
#define XMLVIEWER_H

#include <QDomDocument>
#include <QHash>
#include <QMultiHash>
#include <QIcon>
#include <QTreeWidget>
#include <vector>
#include <Point.h>
#include <PositionVector.h>

using namespace std;
using namespace cxxadt;

class XMLViewer : public QTreeWidget
{
  Q_OBJECT
  
public:

  XMLViewer(QWidget *parent = 0);
  
  bool addTree(QString fileName);
  bool addTree(QDomDocument document, QString fileName);

signals:
  
  void sceneObjectsSelected(QHash<QString, QList<int> >);
  void updateVisualization(QList<QString>);
  void textOutput(QString);
  void setFocus(Point, PositionVector, double);

private slots:
  void sendVisualizationUpdate();
  void selectSceneObjects();
  void removeSelected();
  void setFocus();


private:
  void parseTreeElement(const QDomElement &element, QString *fileName,
			  QTreeWidgetItem *parentItem = 0);
  void parseAttributeElement(const QDomElement &element, QString *fileName,
			     QTreeWidgetItem *parentItem);
  void parseAxisElement(const QDomElement &element, QString *fileName,
			QTreeWidgetItem *parentItem);
  void parseTreeSegmentElement(const QDomElement &element, QString *fileName,
			       QTreeWidgetItem *parentItem);
  void parseBranchingPointElement(const QDomElement &element, QString *fileName,
				  QTreeWidgetItem *parentItem);
  void parseBudElement(const QDomElement &element, QString *fileName,
		       QTreeWidgetItem *parentItem);
  void parseBroadLeafElement(const QDomElement &element, QString *fileName,
		       QTreeWidgetItem *parentItem);
  void deleteItem(QTreeWidgetItem *item);

  QTreeWidgetItem *createItem(const QDomElement &element, QString *fileName,
			      QTreeWidgetItem *parentItem = 0);


  //vector<QDomDocument> documents;
  QString focusedFile;
  QList<QString *> files;
  //QHash<QTreeWidgetItem *, QDomDocument> domDocumentForItem;
  QHash<QString, QHash<QTreeWidgetItem *, int> *> sceneObjectIndexForItem;
  QHash<QTreeWidgetItem *, QString *> fileNameForItem;
  QHash<QString, QTreeWidgetItem*> rootItemForFileName; 
  //QTreeWidgetItem *rootItem;
  
  
};

#endif
