#ifndef LEX_H
#define LEX_H
#include <fstream>
#include <DList.h>
#include <string>

namespace cxxadt{
using namespace std;
#define MAXSTRING 255
enum TOKEN_TYPE {COLON,DOT,FLOAT,ENDFILE,HYPHEN,ID,INT,SLASH};

class Token{
public:
  Token():value(""),type(ENDFILE){}
  Token(const string& token_value, TOKEN_TYPE token_type);
  Token(const Token& token);
  string getValue()const{return value;}
  TOKEN_TYPE getType()const{return type;}
  Token& operator = (const Token& token);
private:
  string value;
  TOKEN_TYPE type;
};


class Lex{
public:
  ~Lex();
  inline Lex& scan(const string& f);
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

inline Lex& Lex::scan(const string& f)
{
  scan(f.c_str());
  return *this;
}
			 
}//close namespace cxxadt

#endif
