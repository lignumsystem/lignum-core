#include <TreeMetaFileParser.h>

//Define the default files for parameters and functions
//initialize file_mode to PARAMETER
TreeMetaFileParser::TreeMetaFileParser(const CString& file)
  :meta_file(file),file_mode(PARAMETER)
{
  //Default paramenter files for different tree compartments and firmament
  file_tables[PARAMETER].insert("Tree","Tree.txt");
  file_tables[PARAMETER].insert("Firmament","Firmament.txt");
  
  //Default file names for different functions
  //1.Foliage mortality
  file_tables[FUNCTION].insert("FoliageMortality","pf.fn");
  //2.Number of New Buds
  file_tables[FUNCTION].insert("Buds","fnb.fn");
  //3.Degree of Interaction (relative shadiness)
  file_tables[FUNCTION].insert("DoI","ip.fn");
  
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

CString TreeMetaFileParser::getParameterFile(const CString& type)
{
  CString file = file_tables[PARAMETER].lookup(type);
  return file;
}

CString TreeMetaFileParser::getFunctionFile(const CString& type)
{
  CString file = file_tables[FUNCTION].lookup(type);
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
  if (token.getType() == ENDFILE){
    return *this;
  }
  //try to parse parameter files
  else if (token.getValue() == CString("Parameters")){
    lex.getToken(); //extract keyword
    lex.getToken(); //extract ':'
    file_mode = PARAMETER;    //change the mode to PARAMETER
    return this->parseFile(); //parse the file name 
  }
  //if no parameter files, try to parse function files
  else if (token.getValue() == CString("Functions")){
    lex.getToken(); //extract keyword
    lex.getToken(); //extract ':'
    file_mode = FUNCTION;   //change the mode to FUNCTION
    return this->parseFile();
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
  CString key;
  CString file_name;

  //last file already parsed, end of file encountered
  if (token.getType() == ENDFILE){
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



