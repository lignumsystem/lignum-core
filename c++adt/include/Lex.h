#ifndef LEX_H
#define LEX_H
#include <fstream.h>
#include <DList.h>
#include <CString.h>

namespace cxxadt{

#define MAXSTRING 255
enum TOKEN_TYPE {COLON,DOT,FLOAT,ENDFILE,HYPHEN,ID,INT,SLASH};

class Token{
public:
  Token():value(""),type(ENDFILE){}
  Token(const CString& token_value, TOKEN_TYPE token_type);
  Token(const Token& token);
  CString getValue()const{return value;}
  TOKEN_TYPE getType()const{return type;}
  Token& operator = (const Token& token);
private:
  CString value;
  TOKEN_TYPE type;
};


class Lex{
public:
  ~Lex();
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

}//close namespace cxxadt

#endif
