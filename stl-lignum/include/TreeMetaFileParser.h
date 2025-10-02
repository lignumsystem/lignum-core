#ifndef TREE_METAFILE_PARSER_H
#define TREE_METAFILE_PARSER_H
#include <stdlib.h>
#include <Table.h>
/// \file TreeMetaFileParser.h
/// \brief Parse initial configuration file usually called MetaFile.txt.
///
/// Parse configuration files and install parameters, Firmament and functions.
#include <Lex.h>

using namespace cxxadt;

namespace Lignum{
///\brief Parse meta file for the tree.
///
///Parse file that lists the files for parameters and functions for the tree
class TreeMetaFileParser{
public:
  ///Define the default files for parameters and functions
  ///initialize file_mode to PARAMETER
  ///I must rethink the functions part: it could become too complicated
  ///to remember to update here and in TreeFriend.cc whenever new functions
  ///emerge. One could have a list or vector of functions and let the 
  ///user define the meaning of each one when implementing metabolic
  ///processes.
  ///\param meta_file The name of The MetaFile.
  TreeMetaFileParser(const string& meta_file);
  ///Install the functions and parameters of the tree
  ///1. Scan and parse the description file ("MetaFile"),
  ///   then the names of the actual files are known<br>
  ///2. Scan and parse the parameter and function files
  ///   (i.e., then the parameters and functions are installed)
  TreeMetaFileParser& parse();
  ///Get parameter file name
  ///\pre User should know parameter file names (e.g. Tree.txt or Firmament.txt)
  ///\param type Parameter file by its type
  ///\retval Parameter file name
  string getParameterFile(const string& type);
  ///Get function file name
  ///\param type Function file by its type
  ///\retval Function file name
  ///\sa fna_str for possible `type` values
  string getFunctionFile(const string& type);
  ///Get the initial tree
  ///\param type Initial tree by its type
  ///\return Initial tree file name
  ///\deprecated L-systems describe initial trees 
  string getTreeInitializationFile(const string& type);
protected:
  ///Parse names for the actual files
  TreeMetaFileParser& parseMetaFile();
  ///Methods parseFiles() and parseFile() do the file name parsing
  ///one by one mutually recursively
  TreeMetaFileParser& parseFiles();
  ///Parsing one file at a time
  TreeMetaFileParser& parseFile();         
private:
  ///Saving parameters, functions and initial files 
  enum FILE_MODE {PARAMETER,FUNCTION,INITIAL};
  FILE_MODE file_mode;
  ///Tables for the parameter files and functions and initialization files
  Table<string,string> file_tables[3]; 
  ///MetaFile describes where the actual files exist
  string meta_file;
  ///Lexical analysator for tokenizing the input file
  Lex lex;               
};

}//End namespace Lignum
#endif //TREE_METAFILE_PARSER_H




