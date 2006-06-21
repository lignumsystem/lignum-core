#ifndef XMLTREE_H
#define XMLTREE_H

#include <XMLDomTreeBuilder.h>
#include <XMLDomTreeReader.h>
#include <XMLDomTreeWriter.h>


// XML WRITING USAGE:
//   
// In order to write a Tree-object to a XML-file one must
// first create a XMLDomTreeWriter-object with the used
// TreeSegment, Bud and Shape (default is Ellipse) template types.
// After that the writing is executed by calling the
// writeTreeToXML-method of the created writer-object with
// the Tree-object and name of the file to created given as arguments. 
//  
//
// Example (ScotsPine):
//  
// ScotsPineTree pine1(/* Arguments of the constructor*/);
//  
// /* Simulation */ 
// 
// XMLDomTreeWriter<ScotsPineSegment, ScotsPineBud> writer;
// writer.writeTreeToXML(pine1, "pine1.xml");
//  
// 
// READING USAGE:
//  
// Reading is done in similar manner as writing: User
// must first create the XMLDomTreeReader-object, and call
// it's writeXMLtoTree-method with the Tree-object and
// file name as arguments. Note that the Tree-object must
// be initialized before the file is read.
//
//
// Example (SugarMaple):
// 
// Tree<SugarMapleSegment, SugarMapleBud> maple(Point(0,0,0), PositionVector(0,0,0));
// XMLDomTreeReader<SugarMapleSegment, SugarMapleBud> reader;
// reader.readXMLToTree(maple, "maple.xml");
 

#endif
