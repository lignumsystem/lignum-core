#ifndef TREE_METAFILE_PARSER_H
#define TREE_METAFILE_PARSER_H
#include <stdlib.h>
#include <Table.h>
#include <Lex.h>

using namespace cxxadt;

class TreeMetaFileParser{
public:
  TreeMetaFileParser(const CString& meta_file);
  TreeMetaFileParser& parse();
  CString getParameterFile(const CString& type);
  CString getFunctionFile(const CString& type);
  CString getTreeInitializationFile(const CString& type);
protected:
  TreeMetaFileParser& parseMetaFile();     //top level method to parse meta file
  TreeMetaFileParser& parseFiles();        //this method does the parsing by
  TreeMetaFileParser& parseFile();         //parsing one file at a time
private:
  enum FILE_MODE {PARAMETER,FUNCTION,INITIAL};
  FILE_MODE file_mode;
  Table<CString,CString> file_tables[3]; //tables for the parameter files and functions
  // and initialization files
  CString meta_file;     //meta file (describes where the actual files exists)
  Lex lex;               //lexical analysator for tokenizing the input file
};

#endif //TREE_METAFILE_PARSER_H




