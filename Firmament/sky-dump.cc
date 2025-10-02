/// \file sky-dump.cc
/// \brief No longer in use
#include <MineSet.h>

#ifdef SKYDUMP
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
  cout << "Usage: sky-dump -def <file> [-mask <file>] [-out <file>]" << endl;
}
 
int main(int argc, char* argv[])
{ 
  FirmamentWithMask f2;
  string arg,empty;
  Token t;
  Lex lex;
  double drp = 0.0;
  double diff_ball_sensor = 0.0;
  ParseCommandLine(argc,argv,"-def",arg);
  
  if (arg == empty){
    Usage();
    exit(0);
  }  
  
  if (arg != empty){
    int incl = 0; int azim = 0;
    lex.scan(arg);
    t = lex.getToken();
    incl = atoi(t.getValue().c_str());
    t = lex.getToken();
    azim = atoi(t.getValue().c_str());
    t = lex.getToken();
    drp = atof(t.getValue().c_str());
    f2.resize(incl,azim,drp);
    diff_ball_sensor =  f2.diffuseBallSensor();
    cout << "Definition from: " << arg << endl;
    cout << "Incl: " << incl << " Azim: " << azim << " Rad: " <<  drp <<endl;
    cout << "Radiation (diffuse ball sensor): " << f2.diffuseBallSensor() << endl;
    cout << "Radiation (diffuse plane sensor): " << f2.diffusePlaneSensor() << endl;
  }

  arg = empty;
  ParseCommandLine(argc,argv,"-mask",arg);
  
  if (arg != empty){
    f2.readMaskFile(arg);
    cout << "Mask file is: " << arg << endl;

    cout << "Radiation with mask (diffuse ball sensor): " <<  f2.diffuseBallSensor()
	 << " Percentage: " << f2.diffuseBallSensor() / diff_ball_sensor * 100.0 << endl;  

    cout << "Radiation with mask (diffuse plane sensor): " << f2.diffusePlaneSensor() 
	 << " Percentage: " << f2.diffusePlaneSensor() / drp * 100.0 << endl;  
  }
  else{
    cout << "No mask file" << endl;
  }

  arg = empty;
  ParseCommandLine(argc,argv,"-out",arg);

  if (arg != empty){
    cout << "Output to: " << arg <<  " and: " << arg <<".schema" << endl; 
    CreateOutPutFile(f2,arg);
  }
  else{
    cout <<"No output file" << endl;
  }

  exit(0);
}

#endif

