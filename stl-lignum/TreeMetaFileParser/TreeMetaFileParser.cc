#include <TreeMetaFileParser.h>

//Define the default files for parameters and functions
//initialize file_mode to PARAMETER
//I must rethink the functions part: it could become too complicated
//to remember to update here and in TreeFriend.cc whenever new functions
//emerge. One could have a list or vector of functions and let the 
//user define the meaning of each one when implementing metabolic
//processes. To access functions GetFunction(tree,1), GetFunction(tree,2)
//or use of mnemonic enumerations should be implemented 
TreeMetaFileParser::TreeMetaFileParser(const string& file)
  :file_mode(PARAMETER),meta_file(file)
{
  //Default paramenter files for different tree compartments and firmament
  file_tables[PARAMETER].insert("Tree","Tree.txt");
  file_tables[PARAMETER].insert("Firmament","Firmament.txt");
  
  //Default file names (keyword file name pair) for different functions
  //1. Adjusted length
  file_tables[FUNCTION].insert("LGMAL","");
  //2.Foliage mortality
  file_tables[FUNCTION].insert("LGMFM","");
  //3.Degree of Interaction (relative shadiness)
  file_tables[FUNCTION].insert("LGMIP","");
  //4.The effect of light to number of the buds. 
  file_tables[FUNCTION].insert("LGMLONB","");
  //5.Number of New Buds
  file_tables[FUNCTION].insert("LGMNB","");
  //6.Function of vigour index
  file_tables[FUNCTION].insert("LGMVI","");
  //7.The effect of vigour index to the number of the buds. 
  file_tables[FUNCTION].insert("LGMVIONB","");


  //Initial tree. Possibly getting obsolete due to L-systems
  file_tables[INITIAL].insert("Tree","");
}

//Install the functions and parameters of the tree
//1. Scan and parse the description file ("meta file"),
//   then the names of the actual files are known
//2. Scan and parse the parameter and function files
//   (i.e., then the parameters and functions are installed)
TreeMetaFileParser& TreeMetaFileParser::parse()
{
  //find out names for the actual files
  this->parseMetaFile(); 

  return *this;
}

string TreeMetaFileParser::getParameterFile(const string& type)
{
  string file = file_tables[PARAMETER].lookup(type);
  return file;
}

string TreeMetaFileParser::getFunctionFile(const string& type)
{
  string file = file_tables[FUNCTION].lookup(type);
  return file;
}

string TreeMetaFileParser::getTreeInitializationFile(const string& type)
{
  string file = file_tables[INITIAL].lookup(type);
  return file;
}

//1.Scan and parse the description file ("meta file")
TreeMetaFileParser& TreeMetaFileParser::parseMetaFile()
{
  lex.scan(meta_file);     //scan and tokenize meta file
  this->parseFiles();      //find the names of the parameter 
  return *this;            //and function files
}

//Parse the name of the files
//1. if end of file then stop
//2. check if parameter or function file
//   change the "mode" to insert the file name 
//   into the right table
TreeMetaFileParser& TreeMetaFileParser::parseFiles()
{
  Token token = lex.peek();

  //end of file, stop parsing
  if (token.getType() == VC_ENDFILE){
    return *this;
  }
  //try to parse parameter files
  else if (token.getValue() == string("Parameters")){
    lex.getToken(); //extract keyword
    lex.getToken(); //extract ':'
    file_mode = PARAMETER;    //change the mode to PARAMETER
    return this->parseFile(); //parse the file name 
  }
  //if no parameter files, try to parse function files
  else if (token.getValue() == string("Functions")){
    lex.getToken(); //extract keyword
    lex.getToken(); //extract ':'
    file_mode = FUNCTION;   //change the mode to FUNCTION
    return this->parseFile();
  }
  //if no function files, try to parse initialization files
  else if (token.getValue() == string("InitialTree")){
    lex.getToken(); //extract keyword
    lex.getToken(); //extract ':'
    file_mode = INITIAL;    //change the mode to INITIAL
    return this->parseFile(); //parse the file name 
  }

  //new file
  else{
    return parseFile();
  }
  //You should never get here
}


//Parse one parameter file name and insert it to parameter files table
TreeMetaFileParser& TreeMetaFileParser::parseFile()
{
  Token token = lex.getToken();
  string key;
  string file_name;

  //last file already parsed, end of file encountered
  if (token.getType() == VC_ENDFILE){
    lex.putToken(token);
    return parseFiles(); //this will stop parsing
  }
  //file name encountered
  else {
    //get the type of tree compartment or purpose of function (the "key")
    key = token.getValue();
    //extract ':' 
    lex.getToken(); 
    token = lex.getToken(); 
    file_name = token.getValue(); 
    //insert the file name to the table
    file_tables[file_mode].insert(key,file_name);
    //parse next file
    return this->parseFiles();
  }
}


#ifdef INITIALIZE_TREE
void Usage()
{
  cout << "Usage: it metafile" << endl;
}

int main(int argc, char *argv[])
{
  
  if (argc != 2){
    Usage();
  }
  else{
    TreeMetaFileParser tmfp(argv[1]);
    tmfp.parse();
  }
  
  exit(0);
}
#endif



