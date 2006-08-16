#ifndef XMLDOMTREEWRITERI_H
#define XMLDOMTREEWRITERI_H

//#include <list>
//#include <QApplication>
#include <QDomDocument>
//#include <QStack>
#include <Lignum.h>
#include <string>
#include <XMLDomTreeBuilder.h>

#include <XMLTree.h>

using namespace Lignum;
using namespace cxxadt;

template <class TS, class BUD = DefaultBud<TS>, class S = Ellipse>
class XMLDomTreeWriter
{
public:
  XMLDomTreeWriter() {}
  bool writeTreeToXML(Tree<TS,BUD>&, const string&);
};

template <class TS, class BUD, class S>
bool XMLDomTreeWriter<TS,BUD,S>::writeTreeToXML(Tree<TS, BUD>& tree, const string& fileName) {
  QDomDocument doc("LMODEL");

  QDomElement root = doc.createElement("Tree"); 
  QDomElement par;

  XMLDomTreeBuilder<TS,BUD,S> XMLDocBuild(doc, root, tree);
  PropagateUp(tree, par, XMLDocBuild); 
  
  QString fname(fileName.c_str());

  QFile file(fname);
  if(!file.open(QIODevice::WriteOnly)) 
    return false;
  
  QIODevice *device = &file;
  
  QTextStream out(device);
  out << doc.toString();
  return true;
  
}

#endif
