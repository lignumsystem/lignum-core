#include <MineSet.h>

//find the command line option and its argument
void ParseCommandLine(int argc, char *argv[],const string& option, string& argument)
{
  int i = 1;
  string command_option,empty;
  bool match = false;

  //loop the command line
  while (i < argc){
    command_option = argv[i];
    if (command_option == option){
      match = true;
      break;//option match
    }
    i++; //jump to next option 
    i++; //
  }
  
  if (match)       //check the command line option argument exits
    argument = argv[++i]; //index the command line option argument
  else
    argument = empty;
}

void Usage()
{
  cout << "Usage: sky-dump [-def <file>] [-mask <file>] -out <file>" << endl;
}
 
int main(int argc, char* argv[])
{ 
  Firmament f1;
  FirmamentWithMask f2;
  string arg,empty;
  Token t;
  Lex lex;
  
  ParseCommandLine(argc,argv,"-def",arg);
  
  if (arg != empty){
    int incl,azim,drp;
    lex.scan(arg);
    t = lex.getToken();
    incl = atoi(t.getValue().c_str());
    t = lex.getToken();
    azim = atoi(t.getValue().c_str());
    t = lex.getToken();
    drp = atof(t.getValue().c_str());
    f2.resize(incl,azim,drp);
    cout << "Definition from: " << arg << endl;
    cout << "Incl: " << incl << " Azim: " << azim << " Rad: " <<  drp <<endl;
  }

  arg = empty;
  ParseCommandLine(argc,argv,"-mask",arg);
  
  if (arg != empty){
    f2.readMaskFile(arg);
    cout << "Mask file is: " << arg << endl;
  }

  ParseCommandLine(argc,argv,"-out",arg);

  if (arg == empty){
    Usage();
  }
  else{
    cout << "Output to: " << arg <<  " and: " << arg <<".schema" << endl; 
    CreateOutPutFile(f2,arg);
  }


  exit(0);
}



