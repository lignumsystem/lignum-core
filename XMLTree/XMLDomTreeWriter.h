#ifndef XMLDOMTREEWRITER_H
#define XMLDOMTREEWRITER_H

#include <list>
//#include <QApplication>
#include <QDomDocument>
#include <QStack>
#include <Lignum.h>
#include <string>
#include <QIODevice>
#include <QFile>
#include <XMLDomTreeBuilder.h>
#include <XMLDomTreeReader.h>

using namespace Lignum;
using namespace cxxadt;

template <class TS, class BUD>
class XMLDomTreeWriter
{
public:
  XMLDomTreeWriter() {}
  bool writeTreeToXML(Tree<TS,BUD>&, const string&);
};

#endif
