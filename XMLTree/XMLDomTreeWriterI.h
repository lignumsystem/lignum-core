#ifndef XMLDOMTREEWRITERI_H
#define XMLDOMTREEWRITERI_H
#include <list>
///\file XMLDomTreeWriterI.h
/// Write Lignum tree to a file as XML representation.
/// Generate Lignum tree XML as std::string.
///
///\par QApplication arrangement for Qt4 and Qt5
///It seems Qt4 is becoming ever more difficult to maintain in MacPorts.
///So far both Qt4 and Qt5 can compile XMLTree for M1 processor and macOS Sonoma.
///XMLDomTreeWriterI.h checks QT_VERSION and includes QApplications accordingly
//Qt4 QApplication include 
#include <QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QApplication>
//Qt5 QApplication include
#else
#include <QtWidgets/QApplication>
#endif
//
#include <QDomDocument>
#include <QStack>
#include <Lignum.h>
#include <sstream>
#include <string>
#include <XMLDomTreeBuilder.h>

using namespace Lignum;
using namespace cxxadt;

template <class TS, class BUD, class S>
bool XMLDomTreeWriter<TS,BUD,S>::writeTreeToXML(Tree<TS, BUD>& tree, const string& fileName)
{
  QDomDocument doc("LMODEL");

  QDomElement root = doc.createElement("Tree"); 
  QDomElement par;

  XMLDomTreeBuilder<TS,BUD,S> XMLDocBuild(doc, root, tree);
  PropagateUp(tree, par, XMLDocBuild); 
  
  QString fname(fileName.c_str());

  QFile file(fname);

  if(!file.open(QIODevice::ReadWrite)){
    cerr << "XMLDomTreeWriter::writeTreeToXML error in opening file" << endl;
    cerr << "Returning false, no output for file " << fileName <<endl;
    return false;
  }
  
  QIODevice *device = &file;
  
  QTextStream out(device);
  out << doc.toString();
  file.close();
  return true;
  
}

template <class TS, class BUD, class S>
string XMLDomTreeWriter<TS,BUD,S>::xmlToString(Tree<TS, BUD>& tree)
{
  QDomDocument doc("LMODEL");

  QDomElement root = doc.createElement("Tree"); 
  QDomElement par;

  XMLDomTreeBuilder<TS,BUD,S> XMLDocBuild(doc, root, tree);
  PropagateUp(tree, par, XMLDocBuild); 
  //-1 = Remove white space from the string
  return doc.toString(-1).toStdString();
  
}

#endif
