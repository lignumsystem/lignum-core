#ifndef XMLDOMTREEWRITERI_H
#define XMLDOMTREEWRITERI_H

#include <list>
#include <QApplication>
#include <QDomDocument>
#include <QStack>
#include <Lignum.h>
#include <sstream>
#include <string>
#include <XMLDomTreeBuilder.h>

using namespace Lignum;
using namespace cxxadt;

template <class TS, class BUD>
class XMLDomTreeWriter
{
public:
  XMLDomTreeWriter() {}
  bool writeTreeToXML(Tree<TS,BUD>&, const string&);
};

template <class TS, class BUD>
bool XMLDomTreeWriter<TS,BUD>::writeTreeToXML(Tree<TS, BUD>& tree, const string& fileName) {
  QDomDocument doc("LMODEL");

  QDomElement root = doc.createElement("Tree"); 
  QDomElement par;

  XMLDomTreeBuilder<TS, BUD> XMLDocBuild(doc, root, tree);
  PropagateUp(tree, par, XMLDocBuild); 
  
  QString fname(fileName.c_str());

  QFile file(fname);
  if(!file.open(QIODevice::WriteOnly)){
    cerr << "XMLDomTreeWriter::writeTreeToXML error in opening file" << endl;
    cerr << "Returning false, no output for file " << fileName <<endl;
    return false;
  }
  
  QIODevice *device = &file;
  
  QTextStream out(device);
  out << doc.toString();
  return true;
  
}

template <class TS,class BUD>
void WriteTreeToXML(int argc, char* argv[],Tree<TS,BUD>& t)
{
  string xmlfile;
  ParseCommandLine(argc,argv,"-xml",xmlfile);
  if (!xmlfile.empty()){
    XMLDomTreeWriter<TS,BUD> writer;
    writer.writeTreeToXML(t, xmlfile);
    cout << "Roots written to a file " << xmlfile <<endl;
  }
  else{
    cout <<  "WriteTreeToXML: no output file" <<endl;
  }
}
#endif
