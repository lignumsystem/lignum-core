#ifndef XMLTREE_H
#define XMLTREE_H
#include <Lignum.h>
#include <XMLDomTreeBuilder.h>
#include <XMLDomTreeReader.h>
#include <XMLDomTreeWriter.h>
/// \file XMLTree.h
/// \brief Read and write Lignum trees to and from XML files
///
/// \note Include this file for Lignum applications
///
/// \par XML Writing
///   
/// In order to write a Tree-object to an XML file one must
/// create a lignumxml::XMLDomTreeWriter object with types
/// for TreeSegment, Bud and leaf Shape for broad-leaved trees.
/// After that the file writing is executed by calling the
/// lignumxml::XMLDomTreeWriter::writeTreeToXML method of the  \c writer object with
/// the Tree object and the name of the file as the two arguments.
/// \code{.cc}
/// ScotsPineTree pine(Point(0,0,0), PositionVector(0,0,0)));
/// XMLDomTreeWriter<ScotsPineSegment, ScotsPineBud> pine_writer;
/// pine_writer.writeTreeToXML(pine, "pine.xml");
/// \endcode
/// For broad-leaved trees user can define leaf shape:
/// \code{.cc}
/// Tree<SugarMapleSegment, SugarMapleBud,Ellipse> maple(Point(0,0,0), PositionVector(0,0,0));
/// XMLDomTreeWriter<ScotsPineSegment, ScotsPineBud, Ellipse> maple_writer;
/// maple_writer.writeTreeToXML(maple, "maple.xml");
/// \endcode
/// \note For Scots pine (or conifers in general) with cylindrical shape of homogenous foliage
/// the leaf shape is ignored. With broad-leaved trees the default leaf Shape is Ellipse.
/// Supported leaf types are cxxadt::Ellipse, cxxadt::Triangle and cxxadt::Kite.
///
/// \par XML Reading
/// Reading is similar to  writing. User creates
/// the lignumxml::XMLDomTreeReader \p reader object, and call it's
/// lignumxml::XMLDomTreeReader::readXMLToTree method with a Tree and a file name as arguments. 
/// \code{.cc}
/// ScotsPineTree pine(Point(0,0,0), PositionVector(0,0,0)));
/// Tree<SugarMapleSegment, SugarMapleBud,Ellipse> maple(Point(0,0,0), PositionVector(0,0,0));
/// Tree<PoplarSegment,PoplarBud,Triangle> poplar(Point(0,0,0), PositionVector(0,0,0));
/// XMLDomTreeReader<ScotsPineSegment, ScostPineBud> pine_reader;
/// XMLDomTreeReader<SugarMapleSegment, SugarMapleBud,Ellipse> > maple_reader;
/// XMLDomTreeReader<Tree<PoplarSegment,PoplarBud,Triangle> > poplar_reader;
/// pine_reader.readXMLToTree(pine,"pine.xml");
/// maple_reader.readXMLToTree(maple,"maple.xml");
/// poplar_reader.readXMLToTree(poplar,"poplar.xml");
/// \endcode
///

///\brief XML file format for Lignum trees 
namespace lignumxml{
  
template <class TS, class BUD, class S>
class XMLDomTreeWriter;

template <class TS, class BUD, class S>
class XMLDomTreeReader;

}
#endif
