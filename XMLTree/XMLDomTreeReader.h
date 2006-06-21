#ifndef XMLDOMTREEREADER_H
#define XMLDOMTREEREADER_H

#include <XMLTree.h>

#include <list>
//#include <QApplication>
#include <QDomDocument>
//#include <QStack>
#include <Lignum.h>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

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

template <class TS, class BUD, class S = Ellipse>
class XMLDomTreeReader
{
public:
  // XMLDomTreeReader(Tree<TS,BUD>& t)
  //:tree(t){}
  XMLDomTreeReader() {}
  Tree<TS,BUD>& readXMLToTree(Tree<TS,BUD>& t, const string& fileName);
private:
  void parseTree(QDomNode&, Tree<TS,BUD>& t); 
  void parseRootAxis(QDomNode&, Axis<TS,BUD>*, Tree<TS,BUD>& );
  Axis<TS,BUD>* parseAxis(QDomNode&, Tree<TS,BUD>& );
  TS* parseTreeSegment(QDomNode&, Tree<TS,BUD>& );
  BranchingPoint<TS,BUD>* parseBranchingPoint(QDomNode&, Tree<TS,BUD>& );
  BUD* parseBud(QDomNode&, Tree<TS,BUD>& );
  BroadLeaf<Triangle>* parseTriangleBroadLeaf(QDomNode&);
  BroadLeaf<Ellipse>* parseEllipseBroadLeaf(QDomNode&);
  void parseTreeParameters(QDomNode&, Tree<TS,BUD>&);
  void parseTreeAttributes(QDomNode&, Tree<TS,BUD>&);
  void parseAxisAttributes(QDomNode&, Axis<TS,BUD>*);
  void parseCfTreeSegmentAttributes(QDomNode&, CfTreeSegment<TS,BUD>*);
  void parseHwTreeSegmentAttributes(QDomNode&, HwTreeSegment<TS,BUD,S>*);
  void parseBranchingPointAttributes(QDomNode&, BranchingPoint<TS,BUD>*);
  void parseBudAttributes(QDomNode&, Bud<TS,BUD>*);
  void parseTriangleBroadLeafAttributes(QDomNode&, BroadLeaf<Triangle>*);
  void parseEllipseBroadLeafAttributes(QDomNode&, BroadLeaf<Ellipse>*);
  void insertLeaf(QDomNode&, HwTreeSegment<TS,BUD,Ellipse>*);
  void insertLeaf(QDomNode&, HwTreeSegment<TS,BUD,Triangle>*); 

  QDomDocument m_doc;			  
  QString segmentType;
  //Tree<TS, BUD>& tree;
};

/**
 * Reads the XML-file to a Tree-object.
 */ 
template <class TS, class BUD, class S>
Tree<TS,BUD>& XMLDomTreeReader<TS,BUD,S>::readXMLToTree(Tree<TS,BUD>& tree, const string& fileName) {
  QString fName(fileName.c_str());
 
  m_doc = QDomDocument("LMODEL");
  QString tmp;

  QFile file(fName);
  if(!file.open(QIODevice::ReadOnly))
    return tree;
  if(!m_doc.setContent(&file)) {
    file.close();
    return tree;
  }
  
  QDomNode root = m_doc.firstChild();

  segmentType = root.toElement().attribute("SegmentType");

  parseTree(root, tree);
  
  file.close();
  return tree;
}

/**
 * Parses the root element of the XML-document
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseTree(QDomNode& root, Tree<TS,BUD>& tree) {
  QDomNode node = root.firstChild();
  QDomNode attrib, param, axisNode; 
    
  // Find the nodes in the DOM-document
  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "TreeAttributes") {
	attrib = node;
      }
      else if(node.nodeName() == "TreeParameters")
	param = node;
      else if(node.nodeName() == "Axis")
	axisNode = node;
    }
    node = node.nextSibling();
  }
  
  // Parse the simulation parameters.
  parseTreeParameters(param, tree);
  
  // Parse the root axis of the tree containing
  // the rest of the components of the tree.
  parseRootAxis(axisNode, &GetAxis(tree), tree);
  
  // Parse the attributes last as some of them need
  // information about the structure of the tree.
  parseTreeAttributes(attrib, tree);

}
  
/**  
 * Parses the root axis of the tree.
 */ 
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
	InsertTreeCompartment(*axis, parseTreeSegment(node, tree));
      }
      // Insert a branching point to the axis
      else if(node.nodeName() == "BranchingPoint") {
	InsertTreeCompartment(*axis, parseBranchingPoint(node, tree));
      }

      // Insert a bud to the axis
      else if(node.nodeName() == "Bud") {
	InsertTreeCompartment(*axis, parseBud(node, tree));
      }
    }
    node = node.nextSibling();
  }
}

/**
 * Parses a axis node to a Axis-object.
 */
template <class TS, class BUD, class S>
Axis<TS, BUD>* XMLDomTreeReader<TS,BUD,S>::parseAxis(QDomNode& axisNode, Tree<TS,BUD>& tree) {
  QDomNode node = axisNode.firstChild();
  QDomNode child;
  Point p;
  PositionVector v;
  QString tmp;
  double x, y, z;
  Axis<TS,BUD>* axis;
  
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
	InsertTreeCompartment(*axis, parseTreeSegment(node, tree));
      }
      if(node.nodeName() == "BranchingPoint") {
	InsertTreeCompartment(*axis, parseBranchingPoint(node, tree));
      }
      else if(node.nodeName() == "Bud") {
	InsertTreeCompartment(*axis, parseBud(node, tree));
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
  TS* ts;
  QDomNode node2 = node.firstChild();
  Point p;
  PositionVector v;
  double x, y, z, go, l, r, rh;
  QString tmp;

  // Search the attribute node of the tree segment
  while(!node2.isNull()) {
    if(node2.isElement()) {
      if(node2.nodeName() == "TreeSegmentAttributes") {
	QDomNode child = node2.firstChild();
	while(!child.isNull()) {
	  if(child.isElement()) {
	    QDomElement element = child.toElement();
	    if(child.nodeName() == "point") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      p = Point(x, y, z);
	    }
	    
	    else if(child.nodeName() == "direction") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      v = PositionVector(x, y, z);
	    }
	    else if(child.nodeName() == "LGAomega") {
	      go = element.text().toDouble();
	    }
	    else if(child.nodeName() == "LGAL") {
	      l = element.text().toDouble();
	    }
	    else if(child.nodeName() == "LGAR") {
	      r = element.text().toDouble();
	    }
	    else if(child.nodeName() == "LGARh") {
	      rh = element.text().toDouble();
	    }
	  }
	  child = child.nextSibling();
	}

	// Object creation
	ts = new TS(p,v,go,l,r,rh,&tree);

	// Parse the rest of the attributes
	if(segmentType == "Cf") {
	  parseCfTreeSegmentAttributes(node2, dynamic_cast<CfTreeSegment<TS,BUD>*>(ts));
	}
	else if(segmentType == "Hw") {
	  parseHwTreeSegmentAttributes(node2, dynamic_cast<HwTreeSegment<TS,BUD,S>*>(ts));
	}
	break;
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
  BranchingPoint<TS,BUD>* bpoint;

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
	      break;
	    }
	  }
	  child = child.nextSibling();
	}
	
	// Object creation
	bpoint = new BranchingPoint<TS, BUD>(p, v, &tree);    
	
	// Parse the rest of the attributes
	parseBranchingPointAttributes(node, bpoint);
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
  BUD* bud;

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
	      break;
	    }
	  }
	  child = child.nextSibling();
	}
	// Object creation
	bud = new BUD(p, v, omega, &tree);
	
	// Parse the rest of the attributes
	parseBudAttributes(node, bud);
	break;
      }
    }
    node = node.nextSibling(); 
  }  

  return bud;
}

template <class TS, class BUD, class S>
BroadLeaf<Triangle>* XMLDomTreeReader<TS,BUD,S>::parseTriangleBroadLeaf(QDomNode& leafNode) {
  BroadLeaf<Triangle>* leaf;
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
	while(!child.isNull()) {
	  if(child.isElement()) {
	    QDomElement element = child.toElement();
	    if(child.nodeName() == "LGAsf") 
	      sf = element.text().toDouble();
	    else if(child.nodeName() == "LGAtauL")
	      tauL = element.text().toDouble();
	    else if(child.nodeName() == "LGAdof")
	      dof = element.text().toDouble();
	    else if(child.nodeName() == "SkySectors")
	      number_of_sectors = element.text().toInt();
	    else if(child.nodeName() == "PetioleStart") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pstart = Point(x, y, z);
	    }
	    else if(child.nodeName() == "PetioleEnd") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pend = Point(x, y, z);
	    }
	    else if(child.nodeName() == "LeafNormal") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      normal = PositionVector(x, y, z);
	    }
	    else if (child.nodeName() == "TriangleLC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      triangleLC = Point(x, y, z);
	    }
	    else if (child.nodeName() == "TriangleRC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      triangleRC = Point(x, y, z);
	    }
	    else if (child.nodeName() == "TriangleAC") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      triangleAC = Point(x, y, z);
	      leaf = new BroadLeaf<Triangle>(sf, tauL, dof, number_of_sectors, Petiole(pstart, pend),
				      normal, Triangle(triangleLC, triangleRC, triangleAC));
	      break;
	    }
	  }
	  child = child.nextSibling();
	}
      
	parseTriangleBroadLeafAttributes(child, leaf);
	break;
      }
    }
    node = node.nextSibling();
  }
  
  return leaf;
}

template <class TS, class BUD, class S>
BroadLeaf<Ellipse>* XMLDomTreeReader<TS,BUD,S>::parseEllipseBroadLeaf(QDomNode& leafNode) {
  BroadLeaf<Ellipse>* leaf;
  QDomNode node = leafNode.firstChild();
  QDomNode child;
  double sf, tauL, dof, x, y, z, eminor, emajor;
  int number_of_sectors;
  Point pstart;
  Point pend;
  
  PositionVector normal;
  QString tmp;

  while(!node.isNull()) {
    if(node.isElement()) {
      if(node.nodeName() == "BroadLeafAttributes") {
	child = node.firstChild();
	while(!child.isNull()) {
	  if(child.isElement()) {
	    QDomElement element = child.toElement();
	    if(child.nodeName() == "LGAsf") 
	      sf = element.text().toDouble();
	    else if(child.nodeName() == "LGAtauL")
	      tauL = element.text().toDouble();
	    else if(child.nodeName() == "LGAdof")
	      dof = element.text().toDouble();
	    else if(child.nodeName() == "SkySectors")
	      number_of_sectors = element.text().toInt();
	    else if(child.nodeName() == "PetioleStart") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pstart = Point(x, y, z);
	    }
	    else if(child.nodeName() == "PetioleEnd") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      pend = Point(x, y, z);
	    }
	    else if(child.nodeName() == "LeafNormal") {
	      tmp = element.text();
	      x = tmp.section(' ', 0, 0).toDouble();
	      y = tmp.section(' ', 1, 1).toDouble();
	      z = tmp.section(' ', 2, 2).toDouble();
	      normal = PositionVector(x, y, z);
	    }
	    else if (child.nodeName() == "EllipseSMajorA") {
	      emajor = element.text().toDouble();
	    }
	    else if (child.nodeName() == "EllipseSMinorA") {
	      eminor = element.text().toDouble();
	      leaf = new BroadLeaf<Ellipse>(sf, tauL, dof, number_of_sectors, Petiole(pstart, pend),
				  normal, Ellipse(pend, PositionVector(pend-pstart), normal, emajor, eminor));
	      break;
	    }

	  }
	  child = child.nextSibling();
	}
      
	parseEllipseBroadLeafAttributes(child, leaf);
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
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGPaf") {
	SetValue(tree, LGPaf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPaleafmax") {
	SetValue(tree, LGPaleafmax, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPapical") {
	SetValue(tree, LGPapical, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPar") {
	SetValue(tree, LGPar, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPdof") {
	SetValue(tree, LGPdof, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPLmin") {
	SetValue(tree, LGPLmin, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPlr") {
	SetValue(tree, LGPlr, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPmf") {
	SetValue(tree, LGPmf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPmr") {
	SetValue(tree, LGPmr, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPms") {
	SetValue(tree, LGPms, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPna") {
	SetValue(tree, LGPna, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPnl") {
	SetValue(tree, LGPnl, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPpr") {
	SetValue(tree, LGPpr, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPq") {
	SetValue(tree, LGPq, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPrhoW") {
	SetValue(tree, LGPrhoW, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPrho_root") {
	SetValue(tree, LGPrho_root, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPrho_hair") {
	SetValue(tree, LGPrho_hair, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPsf") {
	SetValue(tree, LGPsf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPsr") {
	SetValue(tree, LGPsr, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPss") {
	SetValue(tree, LGPss, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPtauL") {
	SetValue(tree, LGPtauL, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPxi") {
	SetValue(tree, LGPxi, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPyc") {
	SetValue(tree, LGPyc, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGPzbrentEpsilon") {
	SetValue(tree, LGPzbrentEpsilon, child.toElement().text().toDouble());
      }
    }
    child = child.nextSibling();
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
  QDomNode child = node.firstChild();
  
  while(!child.isNull()) {
    if(child.isElement()) {
      /*     if(child.nodeName() == "LGAAf") {
	SetValue(*ts, LGAAf, child.toElement().text().toDouble());
	}*/
      if(child.nodeName() == "LGAHf") {
	SetValue(*ts, LGAHf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAP") {
	SetValue(*ts, LGAP, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQin") {
	SetValue(*ts, LGAQin, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQabs") {
	SetValue(*ts, LGAQabs, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGARf") {
	SetValue(*ts, LGARf, child.toElement().text().toDouble());
      }
      /* else if(child.nodeName() == "LGASa") {
	SetValue(*ts, LGASa, child.toElement().text().toDouble());
	}*/
      else if(child.nodeName() == "LGAstarm") {
	SetValue(*ts, LGAstarm, child.toElement().text().toDouble());
      }
      /*      else if(child.nodeName() == "LGAVf") {
	SetValue(*ts, LGAVf, child.toElement().text().toDouble());
	}*/
      else if(child.nodeName() == "LGAWf") {
	SetValue(*ts, LGAWf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWf0") {
	SetValue(*ts, LGAWf0, child.toElement().text().toDouble());
      }
      /*else if(child.nodeName() == "LGAA") {
	SetValue(*ts, LGAA, child.toElement().text().toDouble());
	}
      else if(child.nodeName() == "LGAAh") {
	SetValue(*ts, LGAAh, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAAs") {
	SetValue(*ts, LGAAs, child.toElement().text().toDouble());
	}*/
      else if(child.nodeName() == "LGAAs0") {
	SetValue(*ts, LGAAs0, child.toElement().text().toDouble());
	}
      else if(child.nodeName() == "LGAage") {
	SetValue(*ts, LGAage, child.toElement().text().toDouble());
      }
      /* else if(child.nodeName() == "LGAH") {
	SetValue(*ts, LGAH, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAHTop") {
	SetValue(*ts, LGAHTop, child.toElement().text().toDouble());
	}*/
      else if(child.nodeName() == "LGAL") {
	SetValue(*ts, LGAL, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAM") {
	SetValue(*ts, LGAM, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAomega") {
	SetValue(*ts, LGAomega, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAR") {
	SetValue(*ts, LGAR, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGARh") {
	SetValue(*ts, LGARh, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGARTop") {
	SetValue(*ts, LGARTop, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAvi") {
	SetValue(*ts, LGAvi, child.toElement().text().toDouble());
      }
      /*      else if(child.nodeName() == "LGAV") {
	SetValue(*ts, LGAV, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAVh") {
	SetValue(*ts, LGAVh, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAVs") {
	SetValue(*ts, LGAVs, child.toElement().text().toDouble());
	}*/
      else if(child.nodeName() == "LGAWs") {
	SetValue(*ts, LGAWs, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWh") {
	SetValue(*ts, LGAWh, child.toElement().text().toDouble());
      }
    }
    child = child.nextSibling();
  }
}

/**
 * Parses a hardwood tree segment attribute node and sets the given HwTreeSegment-object's attributes
 * accordingly.
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseHwTreeSegmentAttributes(QDomNode& node, HwTreeSegment<TS,BUD,S>* ts) {
  QDomNode child = node.firstChild();
  
  while(!child.isNull()) {
    if(child.isElement()) {
      /*if(child.nodeName() == "LGAAf") {
	SetValue(*ts, LGAAf, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAHf") {
	SetValue(*ts, LGAHf, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAP") {
	SetValue(*ts, LGAP, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAQin") {
	SetValue(*ts, LGAQin, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQabs") {
	SetValue(*ts, LGAQabs, child.toElement().text().toDouble());
	}*/
      /*      else if(child.nodeName() == "LGARf") {
	SetValue(*ts, LGARf, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGASa") {
	SetValue(*ts, LGASa, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAstarm") {
	SetValue(*ts, LGAstarm, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAVf") {
	SetValue(*ts, LGAVf, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAWf") {
	SetValue(*ts, LGAWf, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAWf0") {
	SetValue(*ts, LGAWf0, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAA") {
	SetValue(*ts, LGAA, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAAh") {
	SetValue(*ts, LGAAh, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAAs") {
	SetValue(*ts, LGAAs, child.toElement().text().toDouble());
	}*/
      if(child.nodeName() == "LGAAs0") {
	SetValue(*ts, LGAAs0, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAage") {
	SetValue(*ts, LGAage, child.toElement().text().toDouble());
      }
      /*else if(child.nodeName() == "LGAH") {
	SetValue(*ts, LGAH, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAHTop") {
	SetValue(*ts, LGAHTop, child.toElement().text().toDouble());
	}*/
      else if(child.nodeName() == "LGAL") {
	SetValue(*ts, LGAL, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAM") {
	SetValue(*ts, LGAM, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAomega") {
	SetValue(*ts, LGAomega, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAR") {
	SetValue(*ts, LGAR, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGARh") {
	SetValue(*ts, LGARh, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGARTop") {
	SetValue(*ts, LGARTop, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAvi") {
	SetValue(*ts, LGAvi, child.toElement().text().toDouble());
      }
      /*else if(child.nodeName() == "LGAV") {
	SetValue(*ts, LGAV, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAVh") {
	SetValue(*ts, LGAVh, child.toElement().text().toDouble());
	}*/
      /*else if(child.nodeName() == "LGAVs") {
	SetValue(*ts, LGAVs, child.toElement().text().toDouble());
	}*/
      else if(child.nodeName() == "LGAWs") {
	SetValue(*ts, LGAWs, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWh") {
	SetValue(*ts, LGAWh, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "BroadLeaf") {
	insertLeaf(child, ts);
      }
      //      else if(child.nodeName() == "BroadLeaf") {
      //	if(child.toElement().attribute("Shape") == "Ellipse") 
      //	  InsertLeaf(*ts, parseEllipseBroadLeaf(child));
	//else if(child.toElement().attribute("Shape") == "Triangle") 
	  //InsertLeaf(*ts, parseTriangleBroadLeaf(child));
    }      
    child = child.nextSibling();
    
  }
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::insertLeaf(QDomNode& node, HwTreeSegment<TS,BUD,Ellipse>* ts) {
  InsertLeaf(*ts, parseEllipseBroadLeaf(node));
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::insertLeaf(QDomNode& node, HwTreeSegment<TS,BUD,Triangle>* ts) {
  InsertLeaf(*ts, parseTriangleBroadLeaf(node));
}

/**
 * Parses a branching point attribute node and sets the given BranchingPoint-object's attributes
 * accordingly.
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseBranchingPointAttributes(QDomNode& node, BranchingPoint<TS,BUD>* bpoint) {
  QDomNode child = node.firstChild();
  
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
      else if(child.nodeName() == "LGAtype") {
	SetValue(*bpoint, LGAtype, child.toElement().text().toDouble());
      }
    }
    child = child.nextSibling();
  }
}

/**
 * Parses a bud attribute node and sets the given Bud-object's attributes
 * accordingly.
 */
template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseBudAttributes(QDomNode& node, Bud<TS,BUD>* bud) {
  QDomNode child = node.firstChild();
  
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGAcollision") {
	SetValue(*bud, LGAcollision, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAip") {
	SetValue(*bud, LGAip, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAomega") {
	SetValue(*bud, LGAomega, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQin") {
	SetValue(*bud, LGAQin, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAstatus") {
	SetValue(*bud, LGAstatus, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAstate") {
	SetValue(*bud, LGAstate, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAtype") {
	SetValue(*bud, LGAtype, child.toElement().text().toDouble());
      }
    }
    child = child.nextSibling();
  }
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseTriangleBroadLeafAttributes(QDomNode& node, BroadLeaf<Triangle>* leaf) {
  QDomNode child = node.firstChild();
  QString tmp;
  
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGAA") {
	SetValue(*leaf, LGAA, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAP") {
	SetValue(*leaf, LGAP, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAM") {
	SetValue(*leaf, LGAM, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQabs") {
	SetValue(*leaf, LGAQabs, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQin") {
	SetValue(*leaf, LGAQin, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWf") {
	SetValue(*leaf, LGAWf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "RadiationVector") {
	vector<double> rv;
	tmp = child.toElement().text();

	for(int i = 0; i < rv.size(); i++) {
	  rv[i] = tmp.section(' ', i, i).toDouble();
	}
	SetRadiationVector(*leaf, rv);
      }
    }
    child = child.nextSibling();
  }
}

template <class TS, class BUD, class S>
void XMLDomTreeReader<TS,BUD,S>::parseEllipseBroadLeafAttributes(QDomNode& node, BroadLeaf<Ellipse>* leaf) {
  QDomNode child = node.firstChild();
  QString tmp;

  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGAA") {
	SetValue(*leaf, LGAA, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAP") {
	SetValue(*leaf, LGAP, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAM") {
	SetValue(*leaf, LGAM, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQabs") {
	SetValue(*leaf, LGAQabs, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAQin") {
	SetValue(*leaf, LGAQin, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWf") {
	SetValue(*leaf, LGAWf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "RadiationVector") {
	vector<double> rv;
	tmp = child.toElement().text();

	for(int i = 0; i < rv.size(); i++) {
	  rv[i] = tmp.section(' ', i, i).toDouble();
	}
	SetRadiationVector(*leaf, rv);
      }
    }
    child = child.nextSibling();
  }
}


#endif
  
