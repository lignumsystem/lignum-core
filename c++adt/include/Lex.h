/// \file Lex.h
/// \brief Simple lexical analyzer.
///
/// Simple lexical analyzer for Lignum simulation configuration files.
#ifndef LEX_H
#define LEX_H



#include <cstring>
#include <DList.h>
#include <fstream>
#include <cstdlib>


using namespace std;

namespace cxxadt{

#define MAXSTRING 255

enum VC_TOKEN_TYPE {VC_COLON,VC_DOT,VC_FLOAT,VC_ENDFILE,VC_HYPHEN,VC_ID,VC_INT,VC_SLASH};

class Token;
class Lex;

class Token{
public:
  Token():value(""),type(VC_ENDFILE){}; 
  Token(const std::string& token_value, VC_TOKEN_TYPE token_type);
  Token(const Token& token);
  std::string getValue()const{return value;}
  VC_TOKEN_TYPE getType()const{return type;}
  Token& operator = (const Token& token);
private:
  std::string value;
  VC_TOKEN_TYPE type;
};




class Lex{
public:
  ~Lex();
  inline Lex& scan(const std::string& f);
  Lex& scan(const char *file);
  Token peek();
  Token getToken();
  Lex& putToken(const Token& token);
protected:
  Lex& scanId();
  Lex& scanNum();
  Lex& scanSpecial();
private:
  ifstream ifile;
  DList token_ls;
};

inline Lex& Lex::scan(const std::string& f)
{
  scan(f.c_str());
  return *this;
}
			 

}//close namespace cxxadt


#endif
