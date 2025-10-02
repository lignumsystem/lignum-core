#ifndef PARSECOMMANDLINE_H
#define PARSECOMMANDLINE_H
#include <string>
/// \file ParseCommandLine.h
/// \brief Functions to check and parse command line in Lignum applications
using namespace std;
///\brief Find argument that follows the flag and returns it in its body
///\param argc Number of command line strings (parameters)
///\param argv Vector of command line strings (parameters)
///\param flag Command line argument starting with `-` character
///\pre The `flag` always begins with the `-` character
///\pre Argument always follows the \p flag
///\return The argument following the \p flag
///\note Seldomly used, see ParseCommandLine(int, char *argv[],const string&, string&) instead.
string ParseCommandLine(int argc, char *argv[],const string& flag);

///\brief Checks if an argument follows the command line flag
///\param argc Number of strings in the command line
///\param argv Vector of strings in the command line
///\param flag Command line flag
///\param[in,out] clarg Command line argument for the \p flag found
///\pre The \p flag must begin with the `-` character
///\pre The \p clarg is an empty string
///\pre The argument \p clarg for the \p flag must not begin with `-` character
///\return True if the \p flag has associated \p clarg argument, False otherwise
///\post If True the \p clarg contains the argument for the \p flag. If False the \p clarg is an empty string.
///\attention Command line accepts Glob expressions. The Glob expression requires protection
///with quotation characters (`'`). ParseCommanLine() returns the Glob expression as it is.
///The actual parsing of the Glob expression must be done where the expression is needed.
bool ParseCommandLine(int argc, char *argv[],const string& flag, string& clarg);

///\brief Check if the command line \p flag exists
///\param argc Number of command line strings (parameters)
///\param argv Vector of command line strings (parameters)
///\param flag Command line argument starting with `-` character
///\pre The `flag` always begins with the `-` character
///\retval True if the \p flag exists, False otherwise
bool CheckCommandLine(int argc, char *argv[],const string& flag);

#endif

