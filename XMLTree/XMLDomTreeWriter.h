#ifndef XMLDOMTREEWRITER_H
#define XMLDOMTREEWRITER_H

//#include <list>
//#include <QApplication>
#include <QDomDocument>
//#include <QStack>
#include <Lignum.h>
#include <string>
#include <XMLDomTreeBuilder.h>


/// \file XMLDomTreeWriter.h
/// \brief Lignum tree to its XML representation.
///
/// Convert Lignum tree to its XML representation. Save the XML to a file
/// or return as STL string.

using namespace Lignum;
using namespace cxxadt;

/// Convert Lignum tree to XML. Save the XML to a file or return the XML as STL string
template <class TS, class BUD, class S = cxxadt::Ellipse>
class XMLDomTreeWriter
{
public:
  XMLDomTreeWriter() {}
  /// Write Lignum tree to an XML file
  /// \param t Lignum tree, either coniferous or broad leaf
  /// \param f File name
  /// \return true if success, false if file input error 
  bool writeTreeToXML(Tree<TS,BUD>& t, const string& f);
  /// Write Lignum tree to an STL string
  /// \param t Lignum tree, either coniferous or broad leaf
  /// \return XML representation of the Lignum tree as stl::string
  /// \post All white space in the return string removed
  /// \sa writeTreeToXML
  string xmlToString(Tree<TS,BUD>& t);
};

/// Helper function to write Lignum tree to an xml file
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

#include <XMLDomTreeWriterI.h>
#endif
