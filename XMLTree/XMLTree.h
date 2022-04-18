#ifndef XMLTREE_H
#define XMLTREE_H
#include <Lignum.h>
#include <XMLDomTreeBuilder.h>
#include <XMLDomTreeReader.h>
#include <XMLDomTreeWriter.h>

/// \file XMLTree.h
/// \brief Read from and write Lignum tree to an XML file.

template <class TS, class BUD, class S>
class XMLDomTreeWriter;

template <class TS, class BUD, class S>
class XMLDomTreeReader;

///\file XMLTree.h 
/// **XML Writing Usage**:
///   
/// In order to write a Tree-object to a XML-file one must
/// first create a XMLDomTreeWriter-object with the used
/// TreeSegment, Bud and Shape (default is Ellipse) template types.
/// After that the writing is executed by calling the
/// writeTreeToXML-method of the created writer-object with
/// the Tree-object and name of the file to created given as arguments. 
///  
///
/// Example (ScotsPine):
///  
/// ScotsPineTree pine1(/* Arguments of the constructor*/);
///  
/// --- Simulation here ---
/// 
/// XMLDomTreeWriter<ScotsPineSegment, ScotsPineBud> writer;
/// writer.writeTreeToXML(pine1, "pine1.xml");
///  
/// 
/// **Reading Usage**:
///  
/// Reading is done in similar manner as writing: User
/// must first create the XMLDomTreeReader-object, and call
/// it's writeXMLtoTree-method with the Tree-object and
/// file name as arguments. Note that the Tree-object must
/// be initialized before the file is read.
///
///
/// Example (SugarMaple):
/// 
/// Tree<SugarMapleSegment, SugarMapleBud> maple(Point(0,0,0), PositionVector(0,0,0));
/// XMLDomTreeReader<SugarMapleSegment, SugarMapleBud> reader;
/// reader.readXMLToTree(maple, "maple.xml");
/// 
/// \note
/// When dealing with broadleaved trees one should always explicitely express the leaf type
///
/// Tree<SugarMapleSegment, SugarMapleBud,Ellipse> maple(Point(0,0,0), PositionVector(0,0,0));
/// Tree<PoplarSegment,PoplarBud,Triangle> poplar(Point(0,0,0), PositionVector(0,0,0));
///
/// XMLDomTreeReader<SugarMapleSegment, SugarMapleBud,Ellipse> >reader;
/// XMLDomTreeReader<Tree<PoplarSegment,PoplarBud,Triangle> >reader;
/// XMLDomTreeWriter<SugarMapleSegment, SugarMapleBud,Ellipse> > writer;
/// XMLDomTreeWriter<Tree<PoplarSegment,PoplarBud,Triangle> > writer;
///
/// The default value is Ellipse so the the reader example for e.g. sugar maple works
/// but other leaf forms like Triangle MUST BE explicitely expressed. Otherwise
/// XMLDomTreeWriter will generate 'Generic' segmentswithout attribute values. The tree 
/// is consequently useless.
 

#endif
