#ifndef XMLDOMTREEREADER_H
#define XMLDOMTREEREADER_H

#include <list>
#include <QApplication>
#include <QDomDocument>
#include <QStack>
#include <Lignum.h>
#include <sstream>
#include <string>

using namespace Lignum;
using namespace cxxadt;

/** 
 * Class for reading a XML-file to a Tree-object. The XML-file
 * must have correct structure (i.e. it is written using the
 * XMLDomTreeWriter class) for the reader to function.
 * 
 * Users must themselves create a empty Tree-object and pass
 * it to the constructor of this class. Tree is then written
 * by calling the readXMLToTree-function of the XMLDomTreeReader-object.
 */

template <class TS, class BUD>
class XMLDomTreeReader
{
public:
  XMLDomTreeReader(Tree<TS,BUD>& t)
  :tree(t){}
  Tree<TS,BUD>& readXMLToTree(const string& fileName);
private:
  void parseTree(QDomNode&); 
  void parseRootAxis(QDomNode&, Axis<TS,BUD>*);
  Axis<TS,BUD>* parseAxis(QDomNode&);
  TS* parseTreeSegment(QDomNode&);
  BranchingPoint<TS,BUD>* parseBranchingPoint(QDomNode&);
  BUD* parseBud(QDomNode&);
  void parseTreeParameters(QDomNode&, Tree<TS,BUD>&);
  void parseTreeAttributes(QDomNode&, Tree<TS,BUD>&);
  void parseAxisAttributes(QDomNode&, Axis<TS,BUD>*);
  void parseCfTreeSegmentAttributes(QDomNode&, CfTreeSegment<TS,BUD>*);
  void parseHwTreeSegmentAttributes(QDomNode&, HwTreeSegment<TS,BUD>*);
  void parseBranchingPointAttributes(QDomNode&, BranchingPoint<TS,BUD>*);
  void parseBudAttributes(QDomNode&, Bud<TS,BUD>*);
			
  QDomDocument m_doc;			  
  QString segmentType;
  Tree<TS, BUD>& tree;
};

/**
 * Reads the XML-file to a Tree-object.
 */ 
template <class TS, class BUD>
Tree<TS,BUD>& XMLDomTreeReader<TS,BUD>::readXMLToTree(const string& fileName) {
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

  parseTree(root);
  
  file.close();
  return tree;
}

/**
 * Parses the root element of the XML-document
 */
template <class TS, class BUD>
void XMLDomTreeReader<TS, BUD>::parseTree(QDomNode& root) {
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
  parseRootAxis(axisNode, &GetAxis(tree));
  
  // Parse the attributes last as some of them need
  // information about the structure of the tree.
  parseTreeAttributes(attrib, tree);

}
  
/**  
 * Parses the root axis of the tree.
 */ 
template <class TS, class BUD>
void XMLDomTreeReader<TS,BUD>::parseRootAxis(QDomNode& axisNode, Axis<TS, BUD>* axis) {
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
	InsertTreeCompartment(*axis, parseTreeSegment(node));
      }
      // Insert a branching point to the axis
      else if(node.nodeName() == "BranchingPoint") {
	InsertTreeCompartment(*axis, parseBranchingPoint(node));
      }

      // Insert a bud to the axis
      else if(node.nodeName() == "Bud") {
	InsertTreeCompartment(*axis, parseBud(node));
      }
    }
    node = node.nextSibling();
  }
}

/**
 * Parses a axis node to a Axis-object.
 */
template <class TS, class BUD>
Axis<TS, BUD>* XMLDomTreeReader<TS, BUD>::parseAxis(QDomNode& axisNode) {
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
	InsertTreeCompartment(*axis, parseTreeSegment(node));
      }
      if(node.nodeName() == "BranchingPoint") {
	InsertTreeCompartment(*axis, parseBranchingPoint(node));
      }
      else if(node.nodeName() == "Bud") {
	InsertTreeCompartment(*axis, parseBud(node));
      }
    }
    node = node.nextSibling();
  }

  return axis;
}

/**
 * Parses a tree segment node to a TreeSegment-object.
 */
template <class TS, class BUD>
TS* XMLDomTreeReader<TS, BUD>::parseTreeSegment(QDomNode& node) {
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
	  parseHwTreeSegmentAttributes(node2, dynamic_cast<HwTreeSegment<TS,BUD>*>(ts));
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
template <class TS, class BUD>
BranchingPoint<TS,BUD>* XMLDomTreeReader<TS,BUD>::parseBranchingPoint(QDomNode& bpNode) {
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
	InsertAxis(*bpoint, parseAxis(node));
      }
    }
    node = node.nextSibling();
  }

  return bpoint;
}

/**
 * Parses a bud node to a Bud-object.
 */
template <class TS, class BUD>
BUD* XMLDomTreeReader<TS, BUD>::parseBud(QDomNode& bNode) {
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

/**
 * Parses the tree parameters node and sets the corresponding parameters
 * accordingly to the given Tree-object.
 */
template <class TS, class BUD>
void XMLDomTreeReader<TS,BUD>::parseTreeParameters(QDomNode& node, Tree<TS,BUD>& tree) {
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
template <class TS, class BUD>
void XMLDomTreeReader<TS, BUD>::parseTreeAttributes(QDomNode& node, Tree<TS, BUD>& tree) {
  cout << "TreeAttributes" << endl;
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
template <class TS, class BUD>
void XMLDomTreeReader<TS,BUD>::parseAxisAttributes(QDomNode& node, Axis<TS,BUD>* axis) {
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
template <class TS, class BUD>
void XMLDomTreeReader<TS,BUD>::parseCfTreeSegmentAttributes(QDomNode& node, CfTreeSegment<TS,BUD>* ts) {
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
template <class TS, class BUD>
void XMLDomTreeReader<TS,BUD>::parseHwTreeSegmentAttributes(QDomNode& node, HwTreeSegment<TS,BUD>* ts) {
  QDomNode child = node.firstChild();
  
  while(!child.isNull()) {
    if(child.isElement()) {
      if(child.nodeName() == "LGAAf") {
	SetValue(*ts, LGAAf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAHf") {
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
      else if(child.nodeName() == "LGASa") {
	SetValue(*ts, LGASa, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAstarm") {
	SetValue(*ts, LGAstarm, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAVf") {
	SetValue(*ts, LGAVf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWf") {
	SetValue(*ts, LGAWf, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAWf0") {
	SetValue(*ts, LGAWf0, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAA") {
	SetValue(*ts, LGAA, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAAh") {
	SetValue(*ts, LGAAh, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAAs") {
	SetValue(*ts, LGAAs, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAAs0") {
	SetValue(*ts, LGAAs0, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAage") {
	SetValue(*ts, LGAage, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAH") {
	SetValue(*ts, LGAH, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAHTop") {
	SetValue(*ts, LGAHTop, child.toElement().text().toDouble());
      }
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
      else if(child.nodeName() == "LGAV") {
	SetValue(*ts, LGAV, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAVh") {
	SetValue(*ts, LGAVh, child.toElement().text().toDouble());
      }
      else if(child.nodeName() == "LGAVs") {
	SetValue(*ts, LGAVs, child.toElement().text().toDouble());
      }
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
 * Parses a branching point attribute node and sets the given BranchingPoint-object's attributes
 * accordingly.
 */
template <class TS, class BUD>
void XMLDomTreeReader<TS,BUD>::parseBranchingPointAttributes(QDomNode& node, BranchingPoint<TS,BUD>* bpoint) {
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
template <class TS, class BUD>
void XMLDomTreeReader<TS,BUD>::parseBudAttributes(QDomNode& node, Bud<TS,BUD>* bud) {
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


#endif
  
