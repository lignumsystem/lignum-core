
#ifndef PARSECOMMANDLINE_H
#define PARSECOMMANDLINE_H

//This asumes that an argument follows the flag and returns it in its body
string ParseCommandLine(int argc, char *argv[],const string& flag);

//This checks if an argument (=string not beginning with character
//'-') follows the flag. The argument or empty string returned in clarg.
bool ParseCommandLine(int argc, char *argv[],const string& flag, string& clarg);

//This checks only if flag appears
bool CheckCommandLine(int argc, char *argv[],const string& flag);

#endif

