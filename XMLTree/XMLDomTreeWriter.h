#ifndef XMLDOMTREEWRITER_H
#define XMLDOMTREEWRITER_H
/// \file XMLDomTreeWriter.h
/// \brief Write Lignum DOM document to XML file
//#include <list>
//#include <QApplication>
#include <QDomDocument>
//#include <QStack>
#include <Lignum.h>
#include <string>
#include <XMLDomTreeBuilder.h>

using namespace Lignum;
using namespace cxxadt;

namespace lignumxml{
///\brief Convert Lignum tree to XML representation.
///Save the XML representation to a file or return the XML as STL string
template <class TS, class BUD, class S = cxxadt::Ellipse>
class XMLDomTreeWriter
{
public:
  XMLDomTreeWriter() {}
  /// Write Lignum tree to an XML file
  /// \param t Lignum tree, either coniferous or broad leaf
  /// \param f File name
  /// \return *true* if success
  /// \return *false* if file open error 
  bool writeTreeToXML(Tree<TS,BUD>& t, const string& f);
  /// Write Lignum tree to an STL string
  /// \param t Lignum tree, either coniferous or broad leaf
  /// \return XML representation of the Lignum tree as stl::string
  /// \post All extra white space in the return string removed
  /// \sa writeTreeToXML
  string xmlToString(Tree<TS,BUD>& t);
};

/// Helper function to write Lignum tree to an xml file
/// \tparam TS Segment type
/// \tparam BUD Bud type
/// \tparam S Leaf shape type (default Ellipse)
/// \param argc Number of command line parameters
/// \param argv Command line
/// \param t Lignum tree, either coniferous or broad leaf
template <class TS,class BUD, class S = cxxadt::Ellipse>
void WriteTreeToXML(int argc, char* argv[],Tree<TS,BUD>& t)
{
  string xmlfile;
  ParseCommandLine(argc,argv,"-xml",xmlfile);
  if (!xmlfile.empty()){
    XMLDomTreeWriter<TS,BUD,S> writer;
    writer.writeTreeToXML(t, xmlfile);
    cout << "Roots written to a file " << xmlfile <<endl;
  }
  else{
    cout <<  "WriteTreeToXML: no output file" <<endl;
  }
}
}
#include <XMLDomTreeWriterI.h>
#endif
