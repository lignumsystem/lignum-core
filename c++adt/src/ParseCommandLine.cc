//Return argument of a flag from the command line as a string

//Note: ParseCommadLine declared in ../include/ParseCommandLine.h

#include <string>

using namespace std;



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
      i++;   //jump to next
    i++;     //command line option
  }
  return clarg;
}

