#include <stdlib.h>
#include <string>
#include <Lex.h>
#include <Firmament.h>
#include <FirmamentWithMask.h>

using namespace sky;

vector<double>  anglesToVector(double incl, double azim)

  //INPUT: inclination (radians) and azimuth (radians)
  //OUTPUT: unit vector pointing to direction defined by inclination and azimuth

{
  vector<double> r;
  r[2] = sin( incl );
  r[0] = cos( incl ) * cos( azim );
  r[1] = cos( incl ) * sin( azim );

  return r;
}


void vectorToAngles(vector<double> direction, double& incl, double& azim)

  //INPUT: unit vector
  //OUTPUT: direction pinted by the unit vector given interms of inclination
  //        and azimuth
{

  double rz, rx,ry;
  double cosIncl;

  if( (rz = direction[2]) < 0.0 ) {
    incl = 0.0;
    azim = 0.0;
    return;
  }

  rx = direction[0];
  ry = direction[1];

  //Change the direction vector (rx, ry, rz) to inclination and azimuth
  incl = asin( rz );

  if(incl > PI_VALUE / 2.0) incl = PI_VALUE / 2.0;
  cosIncl = cos( incl );


  if((rx > R_EPSILON || -rx > R_EPSILON) && cosIncl > R_EPSILON)
    if(ry < 0.0)
      azim = 2.0 * PI_VALUE - acos( rx / cosIncl );
    else
      azim = acos( rx / cosIncl );
  else if(ry > 0.0)
    azim = PI_VALUE / 2.0; 
  else
    azim = 3.0 * PI_VALUE / 4.0; 

  return;
}

void CreateOutPutFile(Firmament& f,string& name)
{
  int i = 0; int r = 0; 
  MJ rad = 0;
  string sfile(name + string(".schema"));
  vector<double> d(3);
  ofstream schema_file(sfile.c_str());
  ofstream data_file(name.c_str());

  schema_file << "input { "<< endl
	      << "file " << "\"" << name << "\"" << ';' << endl
	      << "float X;" << endl 
	      << "float Y;" << endl
	      << "float Z;" << endl 
	      << "float Rad;" << endl
	      << "options separator \':\';" << endl
	      << "}" << endl;
  
  r = f.numberOfRegions();
  for (i = 0; i < r; i++){
    rad = f.diffuseRegionRadiationSum(i,d);
    data_file << d[0] << ":" <<  d[1] << ":" <<  d[2 ] << ":" << rad << endl;
  }
}

#ifdef OUTPUTFILE

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
    cout << "-def " << arg<<endl; 
    int incl,azim,drp;
    lex.scan(arg);
    t = lex.getToken();
    incl = atoi(t.getValue());
    t = lex.getToken();
    azim = atoi(t.getValue());
    t = lex.getToken();
    drp = atof(t.getValue());
    f2.resize(incl,azim,drp);
    cout << "Definition from: " << arg << endl;
    cout << "Incl: " << incl << " Azim: " << azim << " Rad: " <<  drp <<endl;
  }

  arg = empty;
  ParseCommandLine(argc,argv,"-mask",arg);
  
  if (arg != empty){
    cout << "-mask " << arg<<endl; 
    f2.readMaskFile(arg);
    cout << "Mask file is: " << arg << endl;
  }

  ParseCommandLine(argc,argv,"-out",arg);
  
  if (arg == empty){
    Usage();
  }
  else{
    CreateOutPutFile(f2,arg);
    cout << "Output to: " << arg <<  " and: " << arg <<".schema" << endl; 
  }

  exit(0);
}
#endif


