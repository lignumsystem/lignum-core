#ifndef XMLDOMTREEBUILDER_H
#define XMLDOMTREEBUILDER_H

#include <XMLTree.h>

//#include <list>
//#include <QApplication>
#include <QDomDocument>
#include <QStack>
#include <Lignum.h>
//#include <string>

using namespace Lignum;
using namespace cxxadt;

/**
 * Class for building a DOM-document of a given Tree-object.
 * DOM-document is a representation of a XML-document, which can be
 * written to a file. 
 *
 * Note: This class is ONLY for building the DOM-document. To write
 * it to a XML-file use XMLDomTreeWriter-class. 
 */   
template <class TS, class BUD, class S>
class XMLDomTreeBuilder
{
public:
  XMLDomTreeBuilder(QDomDocument& doc, QDomElement& root, Tree<TS,BUD>& tree)
: object_index(0), m_tree(tree), m_doc(doc), m_root(root), segmentTypeFound(false), leafTypeFound(false) {}
  QDomElement& operator() (QDomElement&, TreeCompartment<TS, BUD>*)const ;
  void addTreeCompartmentAttributeNode(QDomElement&, QDomDocument&, TreeCompartment<TS,BUD>*)const;
  void addTreeAttributeNode(QDomElement&, QDomDocument&, Tree<TS,BUD>*)const; 
  void addTreeParameterNode(QDomElement&, QDomDocument&, Tree<TS,BUD>*)const;
  void addTreeFunctionNode(QDomElement&, QDomDocument&, Tree<TS,BUD>*)const;
  void addAxisAttributeNode(QDomElement& node, QDomDocument& m_doc, Axis<TS,BUD>* axis)const;
  void addCfTreeSegmentAttributeNode(QDomElement&, QDomDocument&, CfTreeSegment<TS, BUD>*)const;
  void addHwTreeSegmentAttributeNode(QDomElement&, QDomDocument&, HwTreeSegment<TS, BUD, S>*)const;
  void addBudAttributeNode(QDomElement&, QDomDocument&, Bud<TS, BUD>*)const;
  void addBranchingPointAttributeNode(QDomElement&, QDomDocument&, BranchingPoint<TS,BUD>*)const;
  void addBroadLeafAttributeNode(QDomElement&, QDomDocument&, BroadLeaf<S>*)const;
private:
  mutable int object_index;
  mutable Tree<TS,BUD>& m_tree;
  mutable QDomDocument m_doc;
  mutable QDomElement m_root;
  mutable QString segmentType;
  mutable bool segmentTypeFound;
  mutable QString leafType;
  mutable bool leafTypeFound;
  mutable QStack<QDomElement> m_stack;
  mutable QStack<QDomElement> m_segstack;
};

/**
 * A Functor building the DOM-document. Call PropagateUp -algorithm with the Tree-object and
 * this functor as a arguments to build the DOM-document.
 *
 * Two stacks are used to keep track of traversal in the tree. 
 * 
 */  
template <class TS, class BUD, class S>
QDomElement& XMLDomTreeBuilder<TS, BUD, S>::operator()(QDomElement& prev, TreeCompartment<TS,BUD>* tc)const
{
  QDomElement te, tt, attrib;
  QString tmp;
  
  
  if(Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)) {
    if(m_stack.isEmpty()) {
      if(GetTerminatingBud(*axis) != NULL) {
	te = m_doc.createElement("Axis");
	tmp = QString("NULL");
	addAxisAttributeNode(te, m_doc, axis);
	
	// Main axis always has a terminating bud.
	m_stack.push(te);
      }
    }
    else {
      te = m_doc.createElement("Axis");
      tmp = QString("NULL");

      addAxisAttributeNode(te, m_doc, axis);      
      
      // Push the axis-elements to stacks 
      // if the axis has a terminating bud.

      if((GetTerminatingBud(*axis) != NULL) && GetTreeCompartmentList(*axis).size() > 0){
	m_stack.push(te);
	m_segstack.push(prev);
      }
      else {
	prev.appendChild(te);
      }
      
    }
  }
  else if (TS* ts = dynamic_cast<TS*>(tc)) {
    QDomElement treeSegment = m_doc.createElement("TreeSegment");
    tmp = QString("NULL");
    if(HwTreeSegment<TS,BUD,S>* hw = dynamic_cast<HwTreeSegment<TS,BUD,S>*>(ts)) {
      if(!segmentTypeFound) {
	segmentTypeFound = true;
	m_root.setAttribute("SegmentType", "Hw");
	segmentType = QString("Hw");
      }
      addHwTreeSegmentAttributeNode(treeSegment, m_doc, hw);
    }
    else if (CfTreeSegment<TS,BUD>* cf = dynamic_cast<CfTreeSegment<TS,BUD>*>(ts)) {
      if(!segmentTypeFound) {
	segmentTypeFound = true;
	m_root.setAttribute("SegmentType", "Cf");
	segmentType = QString("Cf");
      }
      addCfTreeSegmentAttributeNode(treeSegment, m_doc, cf);
    }
    else {
      if(!segmentTypeFound) {
	segmentTypeFound = true;	
	m_root.setAttribute("SegmentType", "Generic");
	segmentType = QString("Generic");
      }
    }
    
    // Segment is appended to the children of the node
    // currently being processed.
    m_stack.top().appendChild(treeSegment);

    //prev = treeSegment;
  
  }
  
  else if (BUD* bud = dynamic_cast<BUD*>(tc)) {
    te = m_doc.createElement("Bud");
    addBudAttributeNode(te, m_doc, bud);

    m_stack.top().appendChild(te);
    
    te = m_stack.pop();

    // If m_stack is not empty there are
    // other axes than the main axis yet to
    // be processed.
    if(m_stack.isEmpty() == false) {
      tt = m_segstack.pop();
      tt.appendChild(te);
      prev = tt;
    }
    
    // If the m_stack is empty the end of
    // the main axis is reached and no further
    // processing is necessary.
    else {
      addTreeAttributeNode(m_root, m_doc, &m_tree);
      addTreeParameterNode(m_root, m_doc, &m_tree);
      addTreeFunctionNode(m_root, m_doc, &m_tree);
      m_root.appendChild(te);
      m_doc.appendChild(m_root);
    }
  }
  
  else if (BranchingPoint<TS,BUD>* bpoint = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)) {
    te = m_doc.createElement("BranchingPoint");
    addBranchingPointAttributeNode(te, m_doc, bpoint);
    
    m_stack.top().appendChild(te);

    prev = te;

  }

  return prev;
}

/**
 * A Helper function for adding a TreeCompartmentAttributes-node to the DOM-document.
 */
template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addTreeCompartmentAttributeNode(QDomElement& node, QDomDocument& m_doc, TreeCompartment<TS,BUD>* tc) const{
  QDomElement attrib;
  QString tmp;
  
  Point point = GetPoint(*tc);
  attrib = m_doc.createElement("point");
  tmp = QString("%1 %2 %3").arg(point.getX()).arg(point.getY()).arg(point.getZ());
  attrib.appendChild(m_doc.createTextNode(tmp));
  node.appendChild(attrib);

  PositionVector pvector = GetDirection(*tc);
  attrib = m_doc.createElement("direction");
  tmp = QString("%1 %2 %3").arg(pvector.getX()).arg(pvector.getY()).arg(pvector.getZ());
  attrib.appendChild(m_doc.createTextNode(tmp));
  node.appendChild(attrib);

}

/**
 * A Helper function for adding a TreetAttributes-node to the DOM-document.
 */
template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addTreeAttributeNode(QDomElement& node, QDomDocument& m_doc, Tree<TS,BUD>* tree) const {
  QDomElement rootNode = m_doc.createElement("TreeAttributes");
  QDomElement attrib;
  QString tmp;
 
  addTreeCompartmentAttributeNode(rootNode, m_doc, tree);

  attrib = m_doc.createElement("LGAage");
  tmp = QString("%1").arg(GetValue(*tree, LGAage));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAH");
  tmp = QString("%1").arg(GetValue(*tree, LGAH));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGADbase");
  tmp = QString("%1").arg(GetValue(*tree, LGADbase));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGADbaseHw");
  tmp = QString("%1").arg(GetValue(*tree, LGADbaseHw));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGADbh");
  tmp = QString("%1").arg(GetValue(*tree, LGADbh));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGADbhHw");
  tmp = QString("%1").arg(GetValue(*tree, LGADbhHw));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  node.appendChild(rootNode);
}

/**
 * A Helper function for adding a TreeParameters-node to the DOM-document.
 */
template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addTreeParameterNode(QDomElement& node, QDomDocument& m_doc, Tree<TS,BUD>* tree) const {
  QDomElement rootNode = m_doc.createElement("TreeParameters");
  QDomElement attrib;
  QString tmp;
 
  attrib = m_doc.createElement("LGPaf");
  tmp = QString("%1").arg(GetValue(*tree, LGPaf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPaleafmax");
  tmp = QString("%1").arg(GetValue(*tree, LGPaleafmax));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPapical");
  tmp = QString("%1").arg(GetValue(*tree, LGPapical));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPar");
  tmp = QString("%1").arg(GetValue(*tree, LGPar));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGPdof");
  tmp = QString("%1").arg(GetValue(*tree, LGPdof));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGPLmin");
  tmp = QString("%1").arg(GetValue(*tree, LGPLmin));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPlr");
  tmp = QString("%1").arg(GetValue(*tree, LGPlr));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPmf");
  tmp = QString("%1").arg(GetValue(*tree, LGPmf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPmr");
  tmp = QString("%1").arg(GetValue(*tree, LGPmr));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGPms");
  tmp = QString("%1").arg(GetValue(*tree, LGPms));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPna");
  tmp = QString("%1").arg(GetValue(*tree, LGPna));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPnl");
  tmp = QString("%1").arg(GetValue(*tree, LGPnl));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPpr");
  tmp = QString("%1").arg(GetValue(*tree, LGPpr));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPq");
  tmp = QString("%1").arg(GetValue(*tree, LGPq));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPrhoW");
  tmp = QString("%1").arg(GetValue(*tree, LGPrhoW));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPrho_root");
  tmp = QString("%1").arg(GetValue(*tree, LGPrho_root));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPrho_hair");
  tmp = QString("%1").arg(GetValue(*tree, LGPrho_hair));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPsf");
  tmp = QString("%1").arg(GetValue(*tree, LGPsf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPsr");
  tmp = QString("%1").arg(GetValue(*tree, LGPsr));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPss");
  tmp = QString("%1").arg(GetValue(*tree, LGPss));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPtauL");
  tmp = QString("%1").arg(GetValue(*tree, LGPtauL));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPxi");
  tmp = QString("%1").arg(GetValue(*tree, LGPxi));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPyc");
  tmp = QString("%1").arg(GetValue(*tree, LGPyc));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGPzbrentEpsilon");
  tmp = QString("%1").arg(GetValue(*tree, LGPzbrentEpsilon));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);


  node.appendChild(rootNode);
}

template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addTreeFunctionNode(QDomElement& node, QDomDocument& m_doc, Tree<TS,BUD>* tree) const {
  QDomElement rootNode = m_doc.createElement("TreeFunctions");
  QDomElement attrib;
  QString tmp;
 
  tmp = QString(GetFunction(*tree, LGMAL).getFile().c_str());
  if(tmp != "") {
    attrib = m_doc.createElement("LGMAL");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }

  tmp = QString(GetFunction(*tree, LGMFM).getFile().c_str());
  if(tmp != "") {
    attrib = m_doc.createElement("LGMFM");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }

  tmp = QString(GetFunction(*tree, LGMIP).getFile().c_str());
  if(tmp != "") {
    attrib = m_doc.createElement("LGMIP");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }

  tmp = QString(GetFunction(*tree, LGMNB).getFile().c_str());
  if(tmp != "") {
    attrib = m_doc.createElement("LGMNB");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }

  tmp = QString(GetFunction(*tree, LGMLONB).getFile().c_str());
  if(tmp != "") {
    attrib = m_doc.createElement("LGMLONB");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }
  
  tmp = QString(GetFunction(*tree, LGMVI).getFile().c_str());
  if(tmp != "") {
    attrib = m_doc.createElement("LGMVI");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }

  tmp = QString(GetFunction(*tree, LGMVIONB).getFile().c_str());
  if(tmp != "") {
    attrib = m_doc.createElement("LGMVIONB");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }

  node.appendChild(rootNode);

}

/**
 * A Helper function for adding a AxisAttributes-node to the DOM-document.
 */
template <class TS, class BUD, class S>
//void XMLDomTreeBuilder<TS, BUD>::addAxisAttributeNode(QDomElement& node, Axis<TS,BUD>* axis)  {
void XMLDomTreeBuilder<TS,BUD,S>::addAxisAttributeNode(QDomElement& node, QDomDocument& m_doc, Axis<TS,BUD>* axis) const {
  QDomElement rootNode = m_doc.createElement("AxisAttributes");
  QDomElement attrib;
  QString tmp;
 
  addTreeCompartmentAttributeNode(rootNode, m_doc, axis);

  attrib = m_doc.createElement("LGAstate");
  tmp = QString("%1").arg(GetValue(*axis, LGAstate));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAL");
  tmp = QString("%1").arg(GetValue(*axis, LGAL));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAWf");
  tmp = QString("%1").arg(GetValue(*axis, LGAWf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  node.appendChild(rootNode);
}

/**
 * A Helper function for adding a CfTreeSegmentAttributes-node to the DOM-document.
 */  
template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addCfTreeSegmentAttributeNode(QDomElement& node, QDomDocument& m_doc, CfTreeSegment<TS, BUD>* ts) const {
  QDomElement rootNode = m_doc.createElement("TreeSegmentAttributes");
  QDomElement attrib;
  QString tmp;

  addTreeCompartmentAttributeNode(rootNode, m_doc, ts);
 
  attrib = m_doc.createElement("LGAomega");
  tmp = QString("%1").arg(GetValue(*ts, LGAomega));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAL");
  tmp = QString("%1").arg(GetValue(*ts, LGAL));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAR");
  tmp = QString("%1").arg(GetValue(*ts, LGAR));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGARh");
  tmp = QString("%1").arg(GetValue(*ts, LGARh));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAage");
  tmp = QString("%1").arg(GetValue(*ts, LGAage));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAM");
  tmp = QString("%1").arg(GetValue(*ts, LGAM));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGARTop");
  tmp = QString("%1").arg(GetValue(*ts, LGARTop));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAtype");
  tmp = QString("%1").arg(GetValue(*ts, LGAtype));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAvi");
  tmp = QString("%1").arg(GetValue(*ts, LGAvi));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAWs");
  tmp = QString("%1").arg(GetValue(*ts, LGAWs));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAWh");
  tmp = QString("%1").arg(GetValue(*ts, LGAWh));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAHf");
  tmp = QString("%1").arg(GetValue(*ts, LGAHf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAP");
  tmp = QString("%1").arg(GetValue(*ts, LGAP));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAQin");
  tmp = QString("%1").arg(GetValue(*ts, LGAQin));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAQabs");
  tmp = QString("%1").arg(GetValue(*ts, LGAQabs));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGARf");
  tmp = QString("%1").arg(GetValue(*ts, LGARf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAstarm");
  tmp = QString("%1").arg(GetValue(*ts, LGAstarm));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAVf");
  tmp = QString("%1").arg(GetValue(*ts, LGAVf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAWf");
  tmp = QString("%1").arg(GetValue(*ts, LGAWf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAWf0");
  tmp = QString("%1").arg(GetValue(*ts, LGAWf0));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAsf");
  tmp = QString("%1").arg(GetValue(*ts, LGAsf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  node.setAttribute("ObjectIndex", object_index);
  object_index++;
  node.appendChild(rootNode);
}

/**
 * A Helper function for adding a HwTreeSegmentAttributes-node to the DOM-document.
 */  
template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addHwTreeSegmentAttributeNode(QDomElement& node, QDomDocument& m_doc, HwTreeSegment<TS, BUD, S>* ts) const {
  QDomElement rootNode = m_doc.createElement("TreeSegmentAttributes");
  QDomElement attrib;
  QString tmp;

  addTreeCompartmentAttributeNode(rootNode, m_doc, ts);
  
  attrib = m_doc.createElement("LGAomega");
  tmp = QString("%1").arg(GetValue(*ts, LGAomega));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAL");
  tmp = QString("%1").arg(GetValue(*ts, LGAL));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAR");
  tmp = QString("%1").arg(GetValue(*ts, LGAR));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGARh");
  tmp = QString("%1").arg(GetValue(*ts, LGARh));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAage");
  tmp = QString("%1").arg(GetValue(*ts, LGAage));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAM");
  tmp = QString("%1").arg(GetValue(*ts, LGAM));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGARTop");
  tmp = QString("%1").arg(GetValue(*ts, LGARTop));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAtype");
  tmp = QString("%1").arg(GetValue(*ts, LGAtype));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAvi");
  tmp = QString("%1").arg(GetValue(*ts, LGAvi));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAWs");
  tmp = QString("%1").arg(GetValue(*ts, LGAWs));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAWh");
  tmp = QString("%1").arg(GetValue(*ts, LGAWh));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  node.appendChild(rootNode);

  list<BroadLeaf<S>*>& ll = GetLeafList(*ts);
  
  for(typename list<BroadLeaf<S>*>::iterator i = ll.begin(); i != ll.end(); i++) {
    const Shape& s = static_cast<const Shape&>(GetShape(**i));
    QDomElement leaf = m_doc.createElement("BroadLeaf");
    if(dynamic_cast<const Triangle*>(&s))
      leaf.setAttribute("Shape", "Triangle");
    else
      leaf.setAttribute("Shape", "Ellipse");
    addBroadLeafAttributeNode(leaf, m_doc, *i);
    node.appendChild(leaf);
  }

  node.setAttribute("ObjectIndex", object_index);
  object_index++;

}

/**
 * A Helper function for adding a BudAttributes-node to the DOM-document.
 */  
template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addBudAttributeNode(QDomElement& node, QDomDocument& m_doc, Bud<TS, BUD>* bud) const {
  QDomElement rootNode = m_doc.createElement("BudAttributes");
  QDomElement attrib;
  QString tmp;
 
  addTreeCompartmentAttributeNode(rootNode, m_doc, bud);

  attrib = m_doc.createElement("LGAomega");
  tmp = QString("%1").arg(GetValue(*bud, LGAomega));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAcollision");
  tmp = QString("%1").arg(GetValue(*bud, LGAcollision));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAip");
  tmp = QString("%1").arg(GetValue(*bud, LGAip));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAQin");
  tmp = QString("%1").arg(GetValue(*bud, LGAQin));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAstatus");
  tmp = QString("%1").arg(GetValue(*bud, LGAstatus));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAstate");
  tmp = QString("%1").arg(GetValue(*bud, LGAstate));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAtype");
  tmp = QString("%1").arg(GetValue(*bud, LGAtype));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  node.setAttribute("ObjectIndex", object_index);
  object_index++;
  node.appendChild(rootNode);
}

/**
 * A Helper function for adding a BranchingPointAttributes-node to the DOM-document.
 */  
template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addBranchingPointAttributeNode(QDomElement& node, QDomDocument& m_doc, BranchingPoint<TS,BUD>* bpoint) const {
  QDomElement rootNode = m_doc.createElement("BranchingPointAttributes");
  QDomElement attrib;
  QString tmp;

  addTreeCompartmentAttributeNode(rootNode, m_doc, bpoint);
  

  attrib = m_doc.createElement("LGAMaxD");
  tmp = QString("%1").arg(GetValue(*bpoint, LGAMaxD));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAage");
  tmp = QString("%1").arg(GetValue(*bpoint, LGAage));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAomega");
  tmp = QString("%1").arg(GetValue(*bpoint, LGAomega));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAstate");
  tmp = QString("%1").arg(GetValue(*bpoint, LGAstate));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAtype");
  tmp = QString("%1").arg(GetValue(*bpoint, LGAtype));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  node.appendChild(rootNode);
}

template <class TS, class BUD, class S>
void XMLDomTreeBuilder<TS,BUD,S>::addBroadLeafAttributeNode(QDomElement& node, QDomDocument& m_doc, BroadLeaf<S>* leaf) const {
  QDomElement rootNode = m_doc.createElement("BroadLeafAttributes");
  QDomElement attrib;

  QString tmp;

  attrib = m_doc.createElement("LGAsf");
  tmp = QString("%1").arg(GetValue(*leaf, LGAsf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAtauL");
  tmp = QString("%1").arg(GetValue(*leaf, LGAtauL));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAdof");
  tmp = QString("%1").arg(GetValue(*leaf, LGAdof));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  vector<double> rv = GetRadiationVector(*leaf);

  attrib = m_doc.createElement("SkySectors");
  tmp = QString("%1").arg(rv.size());
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  Petiole p = GetPetiole(*leaf);
  Point sp = GetStartPoint(p);
  Point ep = GetEndPoint(p);
  attrib = m_doc.createElement("PetioleStart");
  tmp = QString("%1 %2 %3").arg(sp.getX()).arg(sp.getY()).arg(sp.getZ());
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("PetioleEnd");
  tmp = QString("%1 %2 %3").arg(ep.getX()).arg(ep.getY()).arg(ep.getZ());
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  PositionVector normal = GetLeafNormal(*leaf);
  attrib = m_doc.createElement("LeafNormal");
  tmp = QString("%1 %2 %3").arg(normal.getX()).arg(normal.getY()).arg(normal.getZ());
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  const Shape& s = static_cast<const Shape&>(GetShape(*leaf));
  if(node.attribute("Shape") == "Triangle") {
    if(!leafTypeFound) {
      leafTypeFound = true;
      m_root.setAttribute("LeafType", "Triangle");
    }
    const Triangle& t = dynamic_cast<const Triangle&>(s);    
    
    attrib = m_doc.createElement("TriangleLC");
    tmp = QString("%1 %2 %3").arg(t.getLeftCorner().getX()).arg(t.getLeftCorner().getY()).arg(t.getLeftCorner().getZ());
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
    
    attrib = m_doc.createElement("TriangleRC");
    tmp = QString("%1 %2 %3").arg(t.getRightCorner().getX()).arg(t.getRightCorner().getY()).arg(t.getRightCorner().getZ());
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);

    attrib = m_doc.createElement("TriangleAC");
    tmp = QString("%1 %2 %3").arg(t.getApexCorner().getX()).arg(t.getApexCorner().getY()).arg(t.getApexCorner().getZ());
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }
  else if (node.attribute("Shape") == "Ellipse") {
    if(!leafTypeFound) {
      leafTypeFound = true;
      m_root.setAttribute("LeafType", "Ellipse");
    }
    const cxxadt::Ellipse& e = dynamic_cast<const cxxadt::Ellipse&>(s);
    //direction of the length of the leaf
    attrib = m_doc.createElement("xdir"); 
    PositionVector x1u = e.x1u();
    tmp = QString("%1 %2 %3").arg(x1u.getX()).arg(x1u.getY()).arg(x1u.getZ());
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);    

    //direction of the width of the leaf 
    attrib = m_doc.createElement("ydir"); 
    PositionVector y1u = e.y1u();
    tmp = QString("%1 %2 %3").arg(y1u.getX()).arg(y1u.getY()).arg(y1u.getZ());
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);   

    attrib = m_doc.createElement("EllipseSMajorA");
    tmp = QString("%1").arg(e.getSemimajorAxis());
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
    
    attrib = m_doc.createElement("EllipseSMinorA");
    tmp = QString("%1").arg(e.getSemiminorAxis());
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }


  attrib = m_doc.createElement("LGAA");
  tmp = QString("%1").arg(GetValue(*leaf, LGAA));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAP");
  tmp = QString("%1").arg(GetValue(*leaf, LGAP));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAM");
  tmp = QString("%1").arg(GetValue(*leaf, LGAM));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAQabs");
  tmp = QString("%1").arg(GetValue(*leaf, LGAQabs));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  attrib = m_doc.createElement("LGAQin");
  tmp = QString("%1").arg(GetValue(*leaf, LGAQin));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);
  
  attrib = m_doc.createElement("LGAWf");
  tmp = QString("%1").arg(GetValue(*leaf, LGAWf));
  attrib.appendChild(m_doc.createTextNode(tmp));
  rootNode.appendChild(attrib);

  
  if(rv.size() >= 1) {
    tmp = QString("%1").arg(rv[0]);
    for(unsigned int i = 1; i < rv.size(); i++) {
      tmp.append(QString(" %1").arg(rv[i]));
    }
    attrib = m_doc.createElement("RadiationVector");
    attrib.appendChild(m_doc.createTextNode(tmp));
    rootNode.appendChild(attrib);
  }

  node.setAttribute("ObjectIndex", object_index);
  object_index++;
  node.appendChild(rootNode);
}

#endif
