
#include "stdafx.h"


#include <Lex.h>
#include <iostream>

//#include <stdlib.h>

using namespace std;

namespace cxxadt{

Token::Token(const std::string& token_value, VC_TOKEN_TYPE token_type)
  :value(token_value),type(token_type)
{
}

Token::Token(const Token& token)
{
  value = token.getValue();
  type = token.getType();
}

Lex::~Lex()
{
  token_ls.goFirst();

  while (!token_ls.isEmpty()){
    Token *token = (Token*) token_ls.getData();
    delete token;
    token_ls.deleteCurrent();
  }
}

Token& Token::operator = (const Token& token)
{
  value = token.value;
  type = token.type;
  return *this;
}

//scan the infile and construct the list of tokens
Lex& Lex::scan(const char *file)
{
  char buf[100];
  ifile.open(file);

  #ifdef _MSC_VER
  if (!ifile)
  {
		CString filename = file;
		MessageBox(NULL, "ERROR: File "+filename+" not found.", NULL, NULL);
		token_ls.insertRight(new Token("ENDFILE",VC_ENDFILE));
		token_ls.goFirst();
		return *this;
  }
  #endif

  token_ls.goFirst();

  if (!ifile){
    cerr << "Lex::scan: could not open input file " << file << endl;
    exit(-1);
  }

  ifile >>  ws; //skip white space
  while (!ifile.eof()){
    char c = ifile.peek();
    if (isalpha(c))      //identifier
      scanId();
    else if (isdigit(c)) //number
      scanNum();
    else if (c == '#')  //comment, skip to the end of line
      ifile.getline(buf,100); 
    else 
      scanSpecial();    //speacial character, see list of token types implemented
    ifile >> ws; //skip white space
  }

  ifile.close();
  
  token_ls.insertRight(new Token("ENDFILE",VC_ENDFILE));
  token_ls.goFirst();

  return *this;
}

Lex& Lex::scanId()
{
  char buffer[MAXSTRING];
  char c;
  Token *token;
  int i = 0;

  while (ifile.get(c)){
    if (isalnum(c) || c=='.' || c=='_')
      buffer[i++]=c;
    else{
      ifile.putback(c);
      break;
    }
  }

  buffer[i] = (char)NULL;

  token = new Token(std::string(buffer),(VC_TOKEN_TYPE)VC_ID);

  token_ls.insertRight(token);

  return *this;
}
  
Lex& Lex::scanNum()
{
  VC_TOKEN_TYPE token_type;
  Token *token;
  char buffer[MAXSTRING];
  char c;
  int i = 0;

  while (ifile.get(c)){
    if (isdigit(c) || c == '.')
      buffer[i++]=c;
    else{
      ifile.putback(c);
      break;
    }
  }

  buffer[i] = (char) NULL;

  if (strstr(buffer,".") == NULL)
    token_type = (VC_TOKEN_TYPE) VC_INT;
  else
    token_type = (VC_TOKEN_TYPE) VC_FLOAT;

  token = new Token(std::string(buffer),token_type);

  token_ls.insertRight(token);

  return *this;
}
      
Lex& Lex::scanSpecial()
{
  char buffer[2];
  char c;
  Token *token;

  ifile.get(c);

  buffer[0] = c;
  buffer[1] = (char)NULL;
  
  switch (c){
  case ':':
    token = new Token(std::string(buffer),(VC_TOKEN_TYPE)VC_COLON);
    break;
  case '.':
    token = new Token(std::string(buffer),(VC_TOKEN_TYPE)VC_DOT);
    break;
  case '-':
    token = new Token(std::string(buffer),(VC_TOKEN_TYPE)VC_HYPHEN);
    break;
  case '/':
    token = new Token(std::string(buffer),(VC_TOKEN_TYPE)VC_SLASH);
    break;
  default:
    cerr << "Unknown token: " << c << endl;
    exit(-1);
  }
  token_ls.insertRight(token);

  return *this;
}

Token Lex::peek()
{
  Token token = *((Token *)token_ls.getData());
  return token;
}

Token Lex::getToken()
{ 
  Token token = *((Token *)token_ls.getData());
  delete (Token *)token_ls.getData();
  token_ls.deleteCurrent();
  return token;
}

Lex& Lex::putToken(const Token& token)
{
  Token *new_token = new Token(token);
  token_ls.insertLeft(new_token);
  return *this;
}

}//closing namespace cxxadt

#ifdef LEX

int main(int argc,char *argv[])
{
  Lex lex;
  Token token;

  lex.scan(argv[argc-1]);
  
  token = lex.getToken();
  while (token.getType() != ENDFILE){
    cout << token.getValue() << " " << token.getType() << endl;
    token = lex.getToken();
  }
  cout << token.getValue() << " " << token.getType() << endl;
  return 0;
}

#endif

