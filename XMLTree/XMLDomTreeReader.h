#ifndef XMLDOMTREEREADER_H
#define XMLDOMTREEREADER_H

#include <list>
#include <QDomDocument>
#include <Lignum.h>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QHash>

using namespace Lignum;
using namespace cxxadt;

/** 
 * Class for reading a XML-file to a Tree-object. The XML-file
 * must have correct structure (i.e. it is written using the
 * XMLDomTreeWriter class) for the reader to function.
 * 
 * Users must themselves create a empty Tree-object and pass
 * it to the  of this class. Tree is then written
 * by calling the readXMLToTree-function of the XMLDomTreeReader-object.
 */
template <class TS, class BUD, class S = cxxadt::Ellipse>
class XMLDomTreeReader
{
public:
  ///\brief XMLDomTreeReader to parse XML tree file
  ///\sa readXMLToTree(Tree<TS,BUD>&, const string&)
  XMLDomTreeReader() {}
  ///\brief Construct a tree from an XML file
  ///\param[in,out] t The tree to be constructed
  ///\param fileName XML file
  ///\return The tree constructed from the \p fileName file
  ///\sa parseTree
  Tree<TS,BUD>& readXMLToTree(Tree<TS,BUD>& t, const string& fileName);
  ///\brief Construct a tree from a QDOmDocument 
  ///\param[in,out] t The tree to be constructed
  ///\param doc QDomDocument representation of an XML file
  ///\return The Tree constructed from the \p doc QDomDocument
  Tree<TS,BUD>& readXMLToTree(Tree<TS,BUD>& t, const QDomDocument& doc);
  int treeType(const string& fileName);
  int leafType(const string& fileName);
  int treeType(const QDomDocument& doc);
  int leafType(const QDomDocument& doc);
  QHash<TreeCompartment<TS,BUD>*, int> getTreeCompartmentHash();
  QHash<BroadLeaf<S>*, int> getLeafHash();

  enum {Cf, Hw};
  enum {TRIANGLE, ELLIPSE, NONE};
private:
  ///\brief Construct the tree from a QDomNode.
  ///
  ///Parse the the XML file represented in QDomNode \p n.
  ///Find the XML nodes for the TreeParameters, TreeAttributes, TreeFunctions
  ///and the Tree main axis. Parse each one of them to construct the tree \p t.
  ///\param n The QDomNode representation of an XML tree file
  ///\param[in,out] t The tree to be constructed
  ///\sa parseRootAxis
  void parseTree(QDomNode& n, Tree<TS,BUD>& t);
  ///\brief Parse the QDomNode\p n representaion of the main axis.
  ///
  ///Parse the main axis representation QDomNode \p n.
  ///Read the main Axis, its attributes and the tree compartments TreeSegments,
  ///Buds and BranchingPoints in \p n
  ///and parse these recursively to construct the tree \p t.
  ///\param n The QDomNode representation of an XML tree file
  ///\param a The main axis of the tree \p t
  ///\param[in,out] t The tree
  ///\sa parseAxis
  ///\sa parseTreeSegment
  ///\sa parseBud
  void parseRootAxis(QDomNode& n, Axis<TS,BUD>* a, Tree<TS,BUD>& t);
  ///\brief Parse single Axis
  ///
  ///Traverse the axis, construct Axis attributes and recursively TreeSegments, BranchingPoints and Buds 
  ///\param n BranchingPoint position in a QDomNode
  ///\param[in] tree The Tree
  ///\return The Axis constructed
  ///\sa parseTreeSegment
  ///\sa parseBranchingPoint
  ///\sa parseBud
  Axis<TS,BUD>* parseAxis(QDomNode& n, Tree<TS,BUD>& tree);
  ///\brief Parse TreeSegment, either CfTreeSegment or HwTreeSegment
  ///\param node QDomNode representing a TreeSegment
  ///\param[in] tree The Tree
  ///\return The TreeSegment constructed
  ///\sa parseCfTreeSegmentAttributes
  ///\sa parseHwTreeSegmentAttributes
  ///\sa insertLeaf
  TS* parseTreeSegment(QDomNode& node, Tree<TS,BUD>& tree);
  ///\brief Parse BranchingPoint
  ///
  ///Parse recursively each axis connectied to a BrachingPoint
  ///\param bpNode QDomNode representing BranchingPoint
  ///\param tree The Tree
  ///\return The BranchingPoint constructed
  ///\sa parseBranchingPointAttributes
  BranchingPoint<TS,BUD>* parseBranchingPoint(QDomNode& bpNode, Tree<TS,BUD>& tree);
  ///\brief Parse Bud
  ///\param bNode QDomNode representing Bud
  ///\param[in] tree The Tree
  ///\return The Bud constructed
  ///\sa parseBudAttributes
  BUD* parseBud(QDomNode& bNode, Tree<TS,BUD>& tree);
  ///\brief Parse Triangle leaf
  ///\param n QDomNode representing Triangle leaf
  ///\return Triangle BroadLeaf constructed
  BroadLeaf<cxxadt::Triangle>* parseTriangleBroadLeaf(QDomNode& n);
  ///\brief Parse Ellipse leaf
  ///\param n QDomNode representing Ellipse leaf
  ///\return Ellipse BroadLeaf constructed
  BroadLeaf<cxxadt::Ellipse>* parseEllipseBroadLeaf(QDomNode& n);
  ///\brief Parse Kite leaf
  ///\param n QDomNode representing Kite leaf
  ///\return Kite BroadLeaf constructed
  BroadLeaf<cxxadt::Kite>* parseKiteBroadLeaf(QDomNode& n);
  void parseTreeParameters(QDomNode&, Tree<TS,BUD>&);
  void parseTreeAttributes(QDomNode&, Tree<TS,BUD>&);
  ///\brief Parse tree function
  ///\param n QDomNode
  ///\param t The tree
  ///\exception ParametricCurveFileException. Catch exception if a function file is not found.
  ///Write error message to standard output and continue building the tree.
  void parseTreeFunctions(QDomNode& n, Tree<TS,BUD>& t);
  void parseAxisAttributes(QDomNode&, Axis<TS,BUD>*);
  void parseCfTreeSegmentAttributes(QDomNode&, CfTreeSegment<TS,BUD>*);
  void parseHwTreeSegmentAttributes(QDomNode&, HwTreeSegment<TS,BUD,S>*);
  void parseBranchingPointAttributes(QDomNode&, BranchingPoint<TS,BUD>*);
  void parseBudAttributes(QDomNode&, Bud<TS,BUD>*);
  ///\brief Parse Triangle leaf attributes
  ///\param n QDomNode representing Tringle leaf
  ///\param[in,out] l Triangle leaf
  void parseTriangleBroadLeafAttributes(QDomNode& n, BroadLeaf<Triangle>* l);
  ///\brief Parse Ellipse leaf attributes
  ///\param n QDomNode representing Ellipse leaf
  ///\param[in,out] l Ellipse leaf
  void parseEllipseBroadLeafAttributes(QDomNode&n , BroadLeaf<cxxadt::Ellipse>* l);
  ///\brief Parse Kite leaf attributes
  ///\param n QDomNode representing Kite leaf
  ///\param[in,out] l Kite leaf
  void parseKiteBroadLeafAttributes(QDomNode&n , BroadLeaf<cxxadt::Kite>* l);
  ///\brief Create and insert Ellipse BroadLeaf
  ///\param n QDomNode representing the BroadLeaf
  ///\param[in,out] ts The TreeSegment with the leaf created
  void insertLeaf(QDomNode& n, HwTreeSegment<TS,BUD,cxxadt::Ellipse>* ts);
  ///\brief Create and insert Triangle BroadLeaf
  ///\param n QDomNode representing the BroadLeaf
  ///\param[in,out] ts The TreeSegment with the leaf created
  void insertLeaf(QDomNode& n, HwTreeSegment<TS,BUD,cxxadt::Triangle>* ts);
  ///\brief Create and insert Kite BroadLeaf
  ///\param n QDomNode representing the BroadLeaf
  ///\param[in,out] ts The TreeSegment with the leaf created
  void insertLeaf(QDomNode& n, HwTreeSegment<TS,BUD,cxxadt::Kite>* ts); 
  QDomDocument m_doc;			  

  // Change this to enum
  QString segmentType;
  QHash<TreeCompartment<TS,BUD>*, int> objectIndexForTreeCompartment;
  QHash<BroadLeaf<S>*, int> objectIndexForLeaf;

};

template <class TS, class BUD, class S>
int XMLDomTreeReader<TS,BUD,S>::treeType(const string& fileName) {
  QString fName(fileName.c_str());
 
  m_doc = QDomDocument("LMODEL");
  QString tmp;

  QFile file(fName);
  if(!file.open(QIODevice::ReadOnly))
    return -1;
  if(!m_doc.setContent(&file)) {
    file.close();
    return -1;
  }
  
  QDomNode root = m_doc.firstChild();

  QString type = root.toElement().attribute("SegmentType");
  if(type == "Cf")
    return XMLDomTreeReader::Cf;
  else
    return XMLDomTreeReader::Hw;
}

template <class TS, class BUD, class S>
int XMLDomTreeReader<TS,BUD,S>::treeType(const QDomDocument& doc) {
  QString type = doc.firstChild().toElement().attribute("SegmentType");
  if(type == "Cf")
    return XMLDomTreeReader::Cf;
  else
    return XMLDomTreeReader::Hw;
}

template <class TS, class BUD, class S>
int XMLDomTreeReader<TS,BUD,S>::leafType(const string& fileName) {
  
  QString fName(fileName.c_str());
 
  m_doc = QDomDocument("LMODEL");
  QString tmp;

  QFile file(fName);
  if(!file.open(QIODevice::ReadOnly))
    return -1;
  if(!m_doc.setContent(&file)) {
    file.close();
    return -1;
  }
  
  QDomNode root = m_doc.firstChild();

  QString type = root.toElement().attribute("LeafType");
  if(type == "Triangle")
    return XMLDomTreeReader::TRIANGLE;
  else
    return XMLDomTreeReader::ELLIPSE;
}

template <class TS, class BUD, class S>
int XMLDomTreeReader<TS,BUD,S>::leafType(const QDomDocument& doc) {
  QString type = doc.firstChild().toElement().attribute("LeafType");
  if(type == "Triangle")
    return XMLDomTreeReader::TRIANGLE;
  else
    return XMLDomTreeReader::ELLIPSE;
}


template <class TS, class BUD, class S>
Tree<TS,BUD>& XMLDomTreeReader<TS,BUD,S>::readXMLToTree(Tree<TS,BUD>& tree, const string& fileName) {
  objectIndexForTreeCompartment.clear();
  objectIndexForLeaf.clear();
  QString fName(fileName.c_str());
 
  m_doc = QDomDocument("LMODEL");
  
  QFile file(fName);
  if(!file.open(QIODevice::ReadOnly)){
    cerr << "XMLDomTreeReader::readXMLToTree: Cannot open file" <<endl;
    cerr << "Exit program" << endl;
    exit(-1);
  }
  if(!m_doc.setContent(&file)) {
    file.close();
    cerr << "XMLDomTreeReader::readXMLToTree: Cannot set XML Dom content" <<endl;
    return tree;
  }
  
  QDomNode root = m_doc.firstChild();

  segmentType = root.toElement().attribute("SegmentType");

  parseTree(root, tree);
  
  file.close();
  return tree;

}

template <class TS, class BUD, class S>
Tree<TS,BUD>& XMLDomTreeReader<TS,BUD,S>::readXMLToTree(Tree<TS,BUD>& tree, const QDomDocument& doc) {
  objectIndexForTreeCompartment.clear();
  objectIndexForLeaf.clear();
  m_doc = doc;
  
  QDomNode root = m_doc.firstChild();

  segmentType = root.toElement().attribute("SegmentType");

  parseTree(root, tree);
  
  return tree;
}

template <class TS, class BUD, class S>
QHash<TreeCompartment<TS,BUD>*, int> XMLDomTreeReader<TS,BUD,S>::getTreeCompartmentHash() 
{
  return objectIndexForTreeCompartment;
}

template <class TS, class BUD, class S>
QHash<BroadLeaf<S>*, int> XMLDomTreeReader<TS,BUD,S>::getLeafHash() {
  return objectIndexForLeaf;
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseTree(QDomNode& root, Tree<TS,BUD>& tree) {
  QDomNode node = root.firstChild();
  QDomNode attrib, param, functions, axisNode; 
  // Find the nodes in the DOM-document
  while(true) {
    if(!node.isNull() && node.isElement()) {
      if(node.nodeName() == "TreeAttributes") {
	attrib = node;
	node = node.nextSibling();
	if(node.isNull() || !node.isElement())
	  break;
      }
      if(node.nodeName() == "TreeParameters") {
	param = node;
	node = node.nextSibling();
	if(node.isNull() || !node.isElement())
	  break;
      }
      if(node.nodeName() == "TreeFunctions") {
	functions = node;
	node = node.nextSibling();
	if(node.isNull() || !node.isElement())
	  break;
      }
      if(node.nodeName() == "Axis") {
	axisNode = node;
	node = node.nextSibling();
	if(node.isNull() || !node.isElement())
	  break;
      }


    }
    break;
  }
  
  
  // Parse the simulation parameters.
  parseTreeParameters(param, tree);
  
  // Parse the root axis of the tree containing
  // the rest of the components of the tree.
  parseRootAxis(axisNode, &GetAxis(tree), tree);
  
  // Parse the attributes last as some of them need
  // information about the structure of the tree.
  parseTreeAttributes(attrib, tree);

  parseTreeFunctions(functions, tree);

}
  
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseRootAxis(QDomNode& axisNode, Axis<TS, BUD>* axis, Tree<TS,BUD>& tree) {
  QDomNode node = axisNode.firstChild();
  QDomNode child;
  QString tmp;
  double x, y, z;

  while(!node.isNull()) {
    if(node.isElement()) {
      
      // Parse the axis attributes
      if(node.nodeName() == "AxisAttributes") {
      	child = node.firstChild();
	while(!child.isNull()) {
	  if(child.isElement()) {
	    // The position and direction of root
	    // axis must be set explicitly 
	    if(child.nodeName() == "point") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      SetPoint(*axis, Point(x, y, z));
	    }
	    
	    else if(child.nodeName() == "direction") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      SetDirection(*axis, PositionVector(x, y, z));
	      break;
	    }
	  }
	  child = child.nextSibling();
	}
	parseAxisAttributes(node, axis);
      }
      // Insert a tree segment to the axis
      else if(node.nodeName() == "TreeSegment") {
	TreeCompartment<TS,BUD>* ts = parseTreeSegment(node, tree);
	InsertTreeCompartment(*axis, ts);
	QString o_index = node.toElement().attribute("ObjectIndex");
	if(!o_index.isEmpty())
	  objectIndexForTreeCompartment.insert(ts, o_index.toInt());
	
      }
      // Insert a branching point to the axis
      else if(node.nodeName() == "BranchingPoint") {
	TreeCompartment<TS,BUD>* bp = parseBranchingPoint(node, tree);
	InsertTreeCompartment(*axis, bp);
	
      }

      // Insert a bud to the axis
      else if(node.nodeName() == "Bud") {
	TreeCompartment<TS,BUD>* bud =  parseBud(node, tree);
	InsertTreeCompartment(*axis, bud);
	QString o_index = node.toElement().attribute("ObjectIndex");
	if(!o_index.isEmpty())
	  objectIndexForTreeCompartment.insert(bud, o_index.toInt());
      }
    }
    node = node.nextSibling();
  }
}

template <class TS, class BUD, class S>
Axis<TS, BUD>* XMLDomTreeReader<TS,BUD,S>::parseAxis(QDomNode& axisNode, Tree<TS,BUD>& tree) {
  QDomNode node = axisNode.firstChild();
  QDomNode child;
  Point p;
  PositionVector v;
  QString tmp;
  double x, y, z;
  Axis<TS,BUD>* axis=NULL;
  
  // Search the axis attributes in the XML-document.
  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "AxisAttributes") {
	child = node.firstChild();
	while(!child.isNull()) {
	  if(child.isElement()) {
	    if(child.nodeName() == "point") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      p = Point(x, y, z);
	    }
	    
	    else if(child.nodeName() == "direction") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      v = PositionVector(x, y, z);
	      break;
	    }
	  }
	  child = child.nextSibling();
	}
	
	// Point and direction attributes are needed for
	// for the creation of the Axis-object.
	axis = new Axis<TS, BUD>(p, v, &tree);
	
	// Rest of the axis' attributes are set here.
	parseAxisAttributes(node, axis);
	break;
      }
    }
    node = node.nextSibling();
  }
  
  node = axisNode.firstChild();
  
  // Process the axis' components 
  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "TreeSegment") {
	TreeCompartment<TS,BUD>* ts = parseTreeSegment(node, tree);
	InsertTreeCompartment(*axis, ts);
	QString o_index = node.toElement().attribute("ObjectIndex");
	if(!o_index.isEmpty())
	  objectIndexForTreeCompartment.insert(ts, o_index.toInt());
	
      }
      // Insert a branching point to the axis
      else if(node.nodeName() == "BranchingPoint") {
	TreeCompartment<TS,BUD>* bp = parseBranchingPoint(node, tree);
	InsertTreeCompartment(*axis, bp);
	
      }
      
      // Insert a bud to the axis
      else if(node.nodeName() == "Bud") {
	TreeCompartment<TS,BUD>* bud =  parseBud(node, tree);
	InsertTreeCompartment(*axis, bud);
	QString o_index = node.toElement().attribute("ObjectIndex");
	if(!o_index.isEmpty())
	  objectIndexForTreeCompartment.insert(bud, o_index.toInt());
      }
    }
    node = node.nextSibling();
  }

  return axis;
}

/**
 * Parses a tree segment node to a TreeSegment-object.
 */
template <class TS, class BUD, class S>
TS* XMLDomTreeReader<TS,BUD,S>::parseTreeSegment(QDomNode& node, Tree<TS,BUD>& tree) {
  TS* ts=NULL;
  QDomNode node2 = node.firstChild();
  Point p;
  PositionVector v;
  double x, y, z, go, l, r, rh;
  x=y=z=go=l=r=rh=0.0;
  QString tmp;

  // Search the attribute node of the tree segment
  while(!node2.isNull()) {
    if(node2.isElement()) {
      if(node2.nodeName() == "TreeSegmentAttributes") {
	QDomNode child = node2.firstChild();
	while(true) {
	  if(!child.isNull() && child.isElement()) {
	    QDomElement element = child.toElement();
	    if(child.nodeName() == "point") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      p = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    
	    if(child.nodeName() == "direction") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      v = PositionVector(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
		      
	    }
	    if(child.nodeName() == "LGAomega") {
	      go = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAL") {
	      l = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAR") {
	      r = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGARh") {
	      rh = element.text().toDouble();
	    }
	  }
	  break;
	}

	child = child.nextSibling();
	// Object creation
	ts = new TS(p,v,go,l,r,rh,&tree);
	//Reset  radius and  heartwood radius,  some  constructors may
	//calculate  these values Implement  constructors that  do not
	//modify values but construct segments as they are given
	SetValue(*ts,LGAR,r);
	SetValue(*ts,LGARh,rh);
	// Parse the rest of the attributes
	if(segmentType == "Cf") {
	  parseCfTreeSegmentAttributes(child, dynamic_cast<CfTreeSegment<TS,BUD>*>(ts));
	}
	else if(segmentType == "Hw") {
	  parseHwTreeSegmentAttributes(child, dynamic_cast<HwTreeSegment<TS,BUD,S>*>(ts));
	}
      }
      
      else if(node2.nodeName() == "BroadLeaf" && segmentType == "Hw") {
	if(HwTreeSegment<TS,BUD,S>* hw = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(ts))
	  insertLeaf(node2, hw);
      }
    }
    node2 = node2.nextSibling();
  }
  return ts;
}

/**
 * Parses branching point node to a BranchingPoint-object.
 */
template <class TS, class BUD, class S>
BranchingPoint<TS,BUD>* XMLDomTreeReader<TS,BUD,S>::parseBranchingPoint(QDomNode& bpNode, Tree<TS,BUD>& tree) {
  QDomNode node = bpNode.firstChild();
  QDomNode child;
  Point p;
  PositionVector v;
  QString tmp;
  double x, y, z;
  BranchingPoint<TS,BUD>* bpoint=NULL;

  // Search the attribute node.
  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "BranchingPointAttributes") {
	child = node.firstChild();
	while(!child.isNull()) {
	  if(child.isElement()) {
	    if(child.nodeName() == "point") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      p = Point(x, y, z);
	    }
	    
	    else if(child.nodeName() == "direction") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      v = PositionVector(x, y, z);
	      child = child.nextSibling();
	      break;
	    }
	  }
	  child = child.nextSibling();
	}
	
	// Object creation
	bpoint = new BranchingPoint<TS, BUD>(p, v, &tree);    
	
	// Parse the rest of the attributes
	parseBranchingPointAttributes(child, bpoint);
	break;
      }
    }
    node = node.nextSibling();
  }
  
  node = bpNode.firstChild();

  // Insert the axes to the branching point
  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "Axis") {
	InsertAxis(*bpoint, parseAxis(node, tree));
      }
    }
    node = node.nextSibling();
  }

  return bpoint;
}

/**
 * Parses a bud node to a Bud-object.
 */
template <class TS, class BUD, class S>
BUD* XMLDomTreeReader<TS,BUD,S>::parseBud(QDomNode& bNode, Tree<TS,BUD>& tree) {
  QDomNode node = bNode.firstChild();
  QDomNode child;
  Point p;
  PositionVector v;
  QString tmp;
  double x, y, z, omega;
  x=y=z=omega=0.0;
  BUD* bud=NULL;

  // Search the attribute node
  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "BudAttributes") {
	child = node.firstChild();
	while(!child.isNull()) {
	  if(child.isElement()) {
	    if(child.nodeName() == "point") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      p = Point(x, y, z);
	    }
	    
	    else if(child.nodeName() == "direction") {
	      tmp = child.toElement().text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      v = PositionVector(x, y, z);
	    }
	    else if(child.nodeName() == "LGAomega") {
	      omega = child.toElement().text().toDouble();
	      child = child.nextSibling();
	      break;
	    }
	  }
	  child = child.nextSibling();
	}
	// Object creation
	bud = new BUD(p, v, omega, &tree);
	
	// Parse the rest of the attributes
	parseBudAttributes(child, bud);
	break;
      }
    }
    node = node.nextSibling(); 
  }  

  return bud;
}

template <class TS, class BUD, class S>
BroadLeaf<cxxadt::Triangle>* XMLDomTreeReader<TS,BUD,S>::parseTriangleBroadLeaf(QDomNode& leafNode) {
  BroadLeaf<cxxadt::Triangle>* leaf;
  QDomNode node = leafNode.firstChild();
  QDomNode child;
  double sf, tauL, dof, x, y, z;
  int number_of_sectors;
  Point pstart;
  Point pend;
  Point triangleLC, triangleRC, triangleAC; 
  
  PositionVector normal;
  QString tmp;

  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "BroadLeafAttributes") {
	child = node.firstChild();
	while(true) {
	
	  if(!child.isNull() && child.isElement()) {
	    QDomElement element = child.toElement();
	    if(child.nodeName() == "LGAsf") { 
	      sf = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAtauL") {
	      tauL = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAdof") { 
	      dof = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "SkySectors") {
	      number_of_sectors = element.text().toInt();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "PetioleStart") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pstart = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "PetioleEnd") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pend = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LeafNormal") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      normal = PositionVector(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "TriangleLC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      triangleLC = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "TriangleRC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      triangleRC = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "TriangleAC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      triangleAC = Point(x, y, z);
	      leaf = new BroadLeaf<Triangle>(sf, tauL, dof, number_of_sectors, Petiole(pstart, pend),
	   			             Triangle(triangleLC, triangleRC, triangleAC));
	      parseTriangleBroadLeafAttributes(child, leaf);
	      child = child.nextSibling();
	      break;
	    }
	  
	  }
	  break;
	}
	break;
      }
    }
    node = node.nextSibling();
  }
  
  return leaf;
}

template <class TS, class BUD, class S>
BroadLeaf<cxxadt::Kite>* XMLDomTreeReader<TS,BUD,S>::parseKiteBroadLeaf(QDomNode& leafNode) {
  BroadLeaf<cxxadt::Kite>* leaf;
  QDomNode node = leafNode.firstChild();
  QDomNode child;
  double sf, tauL, dof, x, y, z;
  int number_of_sectors;
  Point pstart;
  Point pend;
  Point kiteBC, kiteLC, kiteRC, kiteAC; 
  
  PositionVector normal;
  QString tmp;

  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "BroadLeafAttributes") {
	child = node.firstChild();
	while(true) {
	
	  if(!child.isNull() && child.isElement()) {
	    QDomElement element = child.toElement();
	    if(child.nodeName() == "LGAsf") { 
	      sf = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAtauL") {
	      tauL = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAdof") { 
	      dof = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "SkySectors") {
	      number_of_sectors = element.text().toInt();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "PetioleStart") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pstart = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "PetioleEnd") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pend = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LeafNormal") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      normal = PositionVector(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "KiteBC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      kiteBC = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "KiteLC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      kiteLC = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "KiteRC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      kiteRC = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "KiteAC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      kiteAC = Point(x, y, z);
	      leaf = new BroadLeaf<cxxadt::Kite>(sf, tauL, dof, number_of_sectors, Petiole(pstart, pend),
						 cxxadt::Kite(kiteBC,kiteLC, kiteRC,kiteAC));
	      parseKiteBroadLeafAttributes(child, leaf);
	      child = child.nextSibling();
	      break;
	    }
	  
	  }
	  break;
	}
	break;
      }
    }
    node = node.nextSibling();
  }
  
  return leaf;
}


template <class TS, class BUD, class S>
BroadLeaf<cxxadt::Ellipse>* XMLDomTreeReader<TS,BUD,S>::parseEllipseBroadLeaf(QDomNode& leafNode) {
  BroadLeaf<cxxadt::Ellipse>* leaf=NULL;
  QDomNode node = leafNode.firstChild();
  QDomNode child;
  double sf, tauL, dof, x, y, z, eminor, emajor;
  sf=tauL=dof=x=y=z=eminor=emajor=0.0;
  int number_of_sectors=0;
  Point pstart;
  Point pend;
  
  PositionVector normal,x1u,y1u;
  QString tmp;

  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "BroadLeafAttributes") {
	child = node.firstChild();
	while(true) {
	  if(!child.isNull() && child.isElement()) {
	    QDomElement element = child.toElement();
	    if(child.nodeName() == "LGAsf") {
	      sf = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAtauL") {
	      tauL = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LGAdof") {
	      dof = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();	      
	    }
	    if(child.nodeName() == "SkySectors") {
	      number_of_sectors = element.text().toInt();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();	    
	    }
	    if(child.nodeName() == "PetioleStart") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pstart = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "PetioleEnd") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pend = Point(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "LeafNormal") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      normal = PositionVector(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "xdir") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      x1u = PositionVector(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if(child.nodeName() == "ydir") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      y1u = PositionVector(x, y, z);
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "EllipseSMajorA") {
	      emajor = element.text().toDouble();
	      child = child.nextSibling();
	      if(child.isNull() || !child.isElement())
		break;
	      element = child.toElement();
	    }
	    if (child.nodeName() == "EllipseSMinorA") {
	      eminor = element.text().toDouble();
	      leaf = new BroadLeaf<cxxadt::Ellipse>(sf, tauL, dof, number_of_sectors,
						    Petiole(pstart, pend),
						    cxxadt::Ellipse(pend,normal,x1u,y1u,emajor, eminor));
	      //Parse ellipse broadleaf attributes here 
	      parseEllipseBroadLeafAttributes(child, leaf);
	      child = child.nextSibling();
	      break;
	    }
	  }
	  break;
	}
	break;
      }
    }
    node = node.nextSibling();
  }
  return leaf;
}

/**
 * Parses the tree parameters node and sets the corresponding parameters
 * accordingly to the given Tree-object.
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseTreeParameters(QDomNode& node, Tree<TS,BUD>& tree) {
  QDomNode child = node.firstChild();
  
  while(true) {
    if(!child.isNull() && child.isElement()) {
      if(child.nodeName() == "LGPaf") {
	SetValue(tree, LGPaf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPaleafmax") {
	SetValue(tree, LGPaleafmax, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPapical") {
	SetValue(tree, LGPapical, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPar") {
	SetValue(tree, LGPar, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPdof") {
	SetValue(tree, LGPdof, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPLmin") {
	SetValue(tree, LGPLmin, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPlr") {
	SetValue(tree, LGPlr, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPmf") {
	SetValue(tree, LGPmf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPmr") {
	SetValue(tree, LGPmr, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPms") {
	SetValue(tree, LGPms, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPna") {
	SetValue(tree, LGPna, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPnl") {
	SetValue(tree, LGPnl, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPpr") {
	SetValue(tree, LGPpr, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPq") {
	SetValue(tree, LGPq, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPrhoW") {
	SetValue(tree, LGPrhoW, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPrho_root") {
	SetValue(tree, LGPrho_root, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPrho_hair") {
	SetValue(tree, LGPrho_hair, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPsf") {
	SetValue(tree, LGPsf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPsr") {
	SetValue(tree, LGPsr, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPss") {
	SetValue(tree, LGPss, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPtauL") {
	SetValue(tree, LGPtauL, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPxi") {
	SetValue(tree, LGPxi, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPyc") {
	SetValue(tree, LGPyc, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGPzbrentEpsilon") {
	SetValue(tree, LGPzbrentEpsilon, child.toElement().text().toDouble());
      }
    }
    break;
  }
  
}

/**
 * Parses a tree attribute node and sets the corresponding attributes
 * accordingly to the given Tree-object.
 */  
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseTreeAttributes(QDomNode& node, Tree<TS, BUD>& tree) {
  QString tmp;
  double x, y, z;
  QDomNode child = node.firstChild();
  
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "point") {
	tmp = child.toElement().text();
	x = tmp.section(' ', 0, 0).toDouble();
	y = tmp.section(' ', 1, 1).toDouble();
	z = tmp.section(' ', 2, 2).toDouble();
	SetPoint(tree, Point(x, y, z));
      }
      
      else if(child.nodeName() == "direction") {
	tmp = child.toElement().text();
	x = tmp.section(' ', 0, 0).toDouble();
	y = tmp.section(' ', 1, 1).toDouble();
	z = tmp.section(' ', 2, 2).toDouble();
	SetDirection(tree, PositionVector(x, y, z));
      }
      else if(child.nodeName() == "LGAage") {
	SetValue(tree, LGAage, child.toElement().text().toDouble());
      }
      /*      else if(child.nodeName() == "LGAH") {
	SetValue(tree, LGAH, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGADbase") {
	SetValue(tree, LGADbase, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGADbaseHw") {
	SetValue(tree, LGADbaseHw, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGADbh") {
	SetValue(tree, LGADbh, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGADbhHw") {
	SetValue(tree, LGADbhHw, child.toElement().text().toDouble());
	}*/
    }
    child = child.nextSibling();
  }
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseTreeFunctions(QDomNode& node, Tree<TS, BUD>& tree) {
  ParametricCurve function;
  QDomNode child = node.firstChild();
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGMAL") {
	try{
	  function = ParametricCurve(child.toElement().text().toStdString());
	  SetFunction(tree, function, LGMAL);
	}
	catch (ParametricCurveFileException e){
	  cout << "XMLDomTreeReader: could  not find file "<<  e.getFileName() << endl;
	}
      }
      else if(child.nodeName() == "LGMFM") {
	try{
	  function = ParametricCurve(child.toElement().text().toStdString());
	  SetFunction(tree, function, LGMFM);
	}
	catch (ParametricCurveFileException e){
	  cout << "XMLDomTreeReader: could  not find file "<<  e.getFileName() << endl;
	}
      }
      else if(child.nodeName() == "LGMIP") {
	try{
	  function = ParametricCurve(child.toElement().text().toStdString());
	  SetFunction(tree, function, LGMIP);
	}
	catch (ParametricCurveFileException e){
	  cout << "XMLDomTreeReader: could  not find file "<<  e.getFileName() << endl;
	}
      }
      else if(child.nodeName() == "LGMNB") {
	try{
	  function = ParametricCurve(child.toElement().text().toStdString());
	  SetFunction(tree, function, LGMNB);
	}
	catch (ParametricCurveFileException e){
	  cout << "XMLDomTreeReader: could  not find file "<<  e.getFileName() << endl;
	}
      }
      else if(child.nodeName() == "LGMLONB") {
	try{
	  function = ParametricCurve(child.toElement().text().toStdString());
	  SetFunction(tree, function, LGMLONB);
	}
	catch (ParametricCurveFileException e){
	  cout << "XMLDomTreeReader: could  not find file "<<  e.getFileName() << endl;
	}
      }
      else if(child.nodeName() == "LGMVI") {
	try{
	  function = ParametricCurve(child.toElement().text().toStdString());
	  SetFunction(tree, function, LGMVI);
	}
	catch (ParametricCurveFileException e){
	  cout << "XMLDomTreeReader: could  not find file "<<  e.getFileName() << endl;
	}
      }
      else if(child.nodeName() == "LGMVIONB") {
	try{
	  function = ParametricCurve(child.toElement().text().toStdString());
	  SetFunction(tree, function, LGMVIONB);
	}
	catch (ParametricCurveFileException e){
	  cout << "XMLDomTreeReader: could  not find file "<<  e.getFileName() << endl;
	}
      }

    }
    child = child.nextSibling();
  }
}
/**
 * Parses a axis attribute node and sets the given Axis-object's attributes
 * accordingly.
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseAxisAttributes(QDomNode& node, Axis<TS,BUD>* axis) {
  QDomNode child = node.firstChild();
  
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGAstate") {
	SetValue(*axis, LGAstate, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAL") {
	SetValue(*axis, LGAL, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWf") {
	SetValue(*axis, LGAWf, child.toElement().text().toDouble());
      }
    }
    child = child.nextSibling();
  }
}

/**
 * Parses a coniferous tree segment attribute node and sets the given CfTreeSegment-object's attributes
 * accordingly.
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseCfTreeSegmentAttributes(QDomNode& node, CfTreeSegment<TS,BUD>* ts) {
  QDomNode child = node;
  
  while(true) {
    if(!child.isNull() && child.isElement()) {
      if(child.nodeName() == "LGAage") {
	SetValue(*ts, LGAage, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAM") {
	SetValue(*ts, LGAM, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGARTop") {
	SetValue(*ts, LGARTop, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAtype") {
	SetValue(*ts, LGAtype, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }

      if(child.nodeName() == "LGAvi") {
	SetValue(*ts, LGAvi, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWs") {
	SetValue(*ts, LGAWs, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWh") {
	SetValue(*ts, LGAWh, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAHf") {
	SetValue(*ts, LGAHf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAP") {
	SetValue(*ts, LGAP, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQin") {
	SetValue(*ts, LGAQin, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQabs") {
	SetValue(*ts, LGAQabs, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGARf") {
	SetValue(*ts, LGARf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAstarm") {
	SetValue(*ts, LGAstarm, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }//There is no SetValue for LGAVf (LGAVf was accidentally set to LGAstarm)
      if(child.nodeName() == "LGAVf") {
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWf") {
	SetValue(*ts, LGAWf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWf0") {
	SetValue(*ts, LGAWf0, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAsf") {
	SetValue(*ts, LGAsf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }

      /*else if(child.nodeName() == "LGAomega") {
	SetValue(*ts, LGAomega, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAL") {
	SetValue(*ts, LGAL, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAR") {
	SetValue(*ts, LGAR, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGARh") {
	SetValue(*ts, LGARh, child.toElement().text().toDouble());
	}*/
    }
    break;
  }
}

/**
 * Parses a hardwood tree segment attribute node and sets the given HwTreeSegment-object's attributes
 * accordingly.
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseHwTreeSegmentAttributes(QDomNode& node, HwTreeSegment<TS,BUD,S>* ts) {
  QDomNode child = node;
  
  while(true) {
    if(!child.isNull() && child.isElement()) {
      if(child.nodeName() == "LGAage") {
	SetValue(*ts, LGAage, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() && !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAM") {
	SetValue(*ts, LGAM, child.toElement().text().toDouble());
      	child = child.nextSibling();
	if(child.isNull() && !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGARTop") {
	SetValue(*ts, LGARTop, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() && !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAtype") {
	SetValue(*ts, LGAtype, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAvi") {
	SetValue(*ts, LGAvi, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() && !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWs") {
	SetValue(*ts, LGAWs, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() && !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWh") {
	SetValue(*ts, LGAWh, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() && !child.isElement())
	  break;
      }
      /*  while(true) {
	if(child.nodeName() == "BroadLeaf") {
	  insertLeaf(child, ts);
	}
	child = child.nextSibling();
	if(child.isNull() && !child.isElement())
	  break;
	  }*/
    }      
    break;
  }
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::insertLeaf(QDomNode& node, HwTreeSegment<TS,BUD,cxxadt::Ellipse>* ts) {
  BroadLeaf<S>* leaf = parseEllipseBroadLeaf(node);
  InsertLeaf(*ts, leaf);
  QString o_index = node.toElement().attribute(QString("ObjectIndex"));
  if(!o_index.isEmpty())
    objectIndexForLeaf.insert(leaf, o_index.toInt());
  
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::insertLeaf(QDomNode& node, HwTreeSegment<TS,BUD,cxxadt::Triangle>* ts) {
  BroadLeaf<S>* leaf = parseTriangleBroadLeaf(node);
  InsertLeaf(*ts, leaf);
  QString o_index = node.toElement().attribute(QString("ObjectIndex"));
  if(!o_index.isEmpty())
    objectIndexForLeaf.insert(leaf, o_index.toInt());

}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::insertLeaf(QDomNode& node, HwTreeSegment<TS,BUD,cxxadt::Kite>* ts) {
  BroadLeaf<S>* leaf = parseKiteBroadLeaf(node);
  InsertLeaf(*ts, leaf);
  QString o_index = node.toElement().attribute(QString("ObjectIndex"));
  if(!o_index.isEmpty())
    objectIndexForLeaf.insert(leaf, o_index.toInt());

}


template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseBranchingPointAttributes(QDomNode& node, BranchingPoint<TS,BUD>* bpoint) {
  QDomNode child = node;
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGAMaxD") {
	SetValue(*bpoint, LGAMaxD, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAage") {
	SetValue(*bpoint, LGAage, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAomega") {
	SetValue(*bpoint, LGAomega, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAstate") {
	SetValue(*bpoint, LGAstate, child.toElement().text().toDouble());
      }
      //The last attribute, break after it
      else if(child.nodeName() == "LGAtype") {
	SetValue(*bpoint, LGAtype, child.toElement().text().toDouble());
      }
    }
    child = child.nextSibling();
  }
 
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseBudAttributes(QDomNode& node, Bud<TS,BUD>* bud) {
  QDomNode child = node;
  while(true) {
    if(!child.isNull() && child.isElement()) {
      if(child.nodeName() == "LGAcollision") {
	SetValue(*bud, LGAcollision, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAip") {
	SetValue(*bud, LGAip, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQin") {
	SetValue(*bud, LGAQin, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAstatus") {
	SetValue(*bud, LGAstatus, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAstate") {
	SetValue(*bud, LGAstate, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAtype") {
	SetValue(*bud, LGAtype, child.toElement().text().toDouble());
      }
    }
    break;
  }
}

template <class TS, class BUD, class S>
  void XMLDomTreeReader<TS,BUD,S>::parseTriangleBroadLeafAttributes(QDomNode& node, BroadLeaf<cxxadt::Triangle>* leaf) {
  QDomNode child = node;
  QString tmp;
  
  while(true) {
    if(!child.isNull() && child.isElement()) {
      if(child.nodeName() == "LGAA") {
	SetValue(*leaf, LGAA, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAP") {
	SetValue(*leaf, LGAP, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAM") {
	SetValue(*leaf, LGAM, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQabs") {
	SetValue(*leaf, LGAQabs, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQin") {
	SetValue(*leaf, LGAQin, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWf") {
	SetValue(*leaf, LGAWf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "RadiationVector") {
	vector<double> rv(GetRadiationVector(*leaf).size());
	tmp = child.toElement().text();

	for(int i = 0; i < static_cast<int>(rv.size()); i++) {
	  rv[i] = tmp.section(' ', i, i).toDouble();
	}
	SetRadiationVector(*leaf, rv);
      }
    }
    break;
  }
  return;
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseKiteBroadLeafAttributes(QDomNode& node, BroadLeaf<cxxadt::Kite>* leaf) {
  QDomNode child = node;
  QString tmp;
  
  while(true) {
    if(!child.isNull() && child.isElement()) {
      if(child.nodeName() == "LGAA") {
	SetValue(*leaf, LGAA, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAP") {
	SetValue(*leaf, LGAP, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAM") {
	SetValue(*leaf, LGAM, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQabs") {
	SetValue(*leaf, LGAQabs, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQin") {
	SetValue(*leaf, LGAQin, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWf") {
	SetValue(*leaf, LGAWf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "RadiationVector") {
	vector<double> rv(GetRadiationVector(*leaf).size());
	tmp = child.toElement().text();

	for(int i = 0; i < static_cast<int>(rv.size()); i++) {
	  rv[i] = tmp.section(' ', i, i).toDouble();
	}
	SetRadiationVector(*leaf, rv);
      }
    }
    break;
  }
  return;
}
 
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseEllipseBroadLeafAttributes(QDomNode& node, BroadLeaf<cxxadt::Ellipse>* leaf) {
  QDomNode child = node;
  QString tmp;
  while(true) {
    if(!child.isNull() && child.isElement()) {
       if(child.nodeName() == "LGAA") {
	SetValue(*leaf, LGAA, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAP") {
	SetValue(*leaf, LGAP, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAM") {
	SetValue(*leaf, LGAM, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQabs") {
	SetValue(*leaf, LGAQabs, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAQin") {
	SetValue(*leaf, LGAQin, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }
      if(child.nodeName() == "LGAWf") {
	SetValue(*leaf, LGAWf, child.toElement().text().toDouble());
	child = child.nextSibling();
	if(child.isNull() || !child.isElement())
	  break;
      }

      if(child.nodeName() == "RadiationVector") {
	vector<double> rv(GetRadiationVector(*leaf).size());
	tmp = child.toElement().text();
	for(unsigned int i = 0; i < rv.size() ; i++) {
	  rv[i] = tmp.section(' ', i, i).toDouble();
	}
	SetRadiationVector(*leaf, rv);
      }
    }

     
    break;
  }
}


#endif
  
