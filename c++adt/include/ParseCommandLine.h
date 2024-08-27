#ifndef PARSECOMMANDLINE_H
#define PARSECOMMANDLINE_H
#include <string>
///\file ParseCommandLine.h
using namespace std;
///\brief Find argument that follows the flag and returns it in its body
///\param argc Number of command line strings (parameters)
///\param argv Vector of command line strings (parameters)
///\param flag Command line argument starting with `-` character
///\pre The `flag` always begins with the `-` character
///\pre Argument always follows the \p flag
///\return The argument following the \p flag 
string ParseCommandLine(int argc, char *argv[],const string& flag);

///\brief Checks if an argument follows the command line flag
///\param argc Number of strings in the command line
///\param argv Vector of strings in the command line
///\param flag Command line flag
///\param clarg Command line argument
///\pre The \p flag always begins with the `-` character
///\pre The \p clarg never begins with the `-`character
///\return True if the \p flag has associated \p clarg argument, False otherwise
///\post If not True the \p clarg is an empty string
///\attention Command line accepts Glob expressions. The Glob expression requires protection
///with quotation characters (`'`). ParseCommanLine() returns the Glob expression as it is.
///The actual parsing of the Glob expression must be done where the expression is needed.
bool ParseCommandLine(int argc, char *argv[],const string& flag, string& clarg);

///\brief Check if the command line \p flag appears
///\param argc Number of command line strings (parameters)
///\param argv Vector of command line strings (parameters)
///\param flag Command line argument starting with `-` character
///\pre The `flag` always begins with the `-` character
///\retval True if the \p flag exists, False otherwise
bool CheckCommandLine(int argc, char *argv[],const string& flag);

#endif

