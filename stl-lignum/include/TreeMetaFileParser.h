#ifndef TREE_METAFILE_PARSER_H
#define TREE_METAFILE_PARSER_H
#include <stdlib.h>
#include <Table.h>
#include <Lex.h>
#include <LGMSymbols.h>
using namespace Lignum;
using namespace cxxadt;

namespace Lignum{

  class TreeMetaFileParser{
  public:
    TreeMetaFileParser(const string& meta_file);
    TreeMetaFileParser& parse();
    string getParameterFile(const string& type);
    string getFunctionFile(const string& type);
    string getTreeInitializationFile(const string& type);
  protected:
    TreeMetaFileParser& parseMetaFile();     //top level method to parse meta file
    TreeMetaFileParser& parseFiles();        //this method does the parsing by
    TreeMetaFileParser& parseFile();         //parsing one file at a time
  private:
    FILE_MODE file_mode;  //which part of the config file is being parsed  
    Table<string,string> file_tables[4]; //tables for the parameter files, 
                                         //functions, graphics and initialization files
    string meta_file;     //meta file (describes where the actual files exists)
    Lex lex;              //lexical analysator for tokenizing the input file
  };

}//closing namespace Lignum
#endif //TREE_METAFILE_PARSER_H
