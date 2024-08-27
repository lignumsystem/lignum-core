//Return argument of a flag from the command line as a string
//Note: ParseCommadLine declared in ../include/ParseCommandLine.h
#include <ParseCommandLine.h>
#include <string>

using namespace std;


//This asumes that an argument follows the flag and returns it in its body
string ParseCommandLine(int argc, char *argv[],const string& flag)
{
  int i = 1;
  string clarg;  //obviously initialized as empty string
  
  //loop through command line options, argc - 1 checks possible
  //missing last argument to command line option does not cause core
  //dump
  while (i < argc - 1){
    if (string(argv[i]) == flag){
      clarg = argv[++i]; //pick the argument to command line option
      break;
    }
    else
      i++;   //jump to next command line item
  }
  return clarg;
}


//This checks if an argument (=string not beginning with character
//'-') follows the flag. The argument or empty string returned in clarg.
bool ParseCommandLine(int argc, char *argv[],const string& flag, string& clarg)
{
  int i = 1;
  bool found = false;
  //loop through command line options
  while (i < argc){
    if (string(argv[i]) == flag){
      found = true;
      //pick the argument to command line option if exists, check
      //first that we are not already at the last argument
      if( (string(argv[i+1])[0] != '-') && (i < argc - 1) )
	clarg = argv[++i]; //pick the argument to command line option
      else
	clarg = "";
      break;
    }
    else
      i++;   //jump to next item on command line
  }
  return found;
}


//This checks only if flag appears

bool CheckCommandLine(int argc, char *argv[],const string& flag)
{
  int i = 1;
  bool found = false;

  //loop through command line options
  while (i < argc){
    if (string(argv[i]) == flag) {
      found = true;
      break;
	}
    else
      i++;   //jump to next item on command line
  }
  return found;
}

