
#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>

namespace cxxadt{
  using namespace std;
/*======================================================================================
**Class CString implements some operations on string
**A friends:
**1. operator << : output
**2. operator +  : string concatenation, (returns new string)
**3. operator == : string equality
**B methods:
**1.the "default" constructor 
**2.the copy constructor
**3.the destructor
**4.the assignment
**5.add and assign (a = "hello";b ="world"; a+=b --> a == "helloworld")
**6.the length of the string
**7.strStr implements the "strstr" library function
**8.subStr returns the substring (a = "helloworld"; a.subStr(1,4)--> "ello")
**9.toLower converts the string to lowercase (a = "HELLO"; a.toLower --> a == "hello")
**10.isSpace checks if the string has only whitespace characters
**   (a = "    "; a.isSpace() == 1;
**11.the type cast operator (returns the character vector "string")
**====================================================================================*/
class CString{
friend ostream& operator<<(ostream&,const CString& );
friend CString operator + (const CString&, const CString&);
friend inline int operator != (const CString&, const CString&);
friend inline int operator == (const CString&, const CString&);
public:
  inline CString(const char * str= "");
  inline CString(const CString& str);
  ~CString(){delete [] string; str_length = -1;}
  CString& operator=(const CString& str);
  CString& operator+=(const CString& str);
  int length()const {return str_length;}
  inline CString strStr(const CString& str)const;
  CString subStr(unsigned int start_Pos, unsigned int end_pos)const;
  inline CString& toLower();
  inline int isSpace();
  operator const char*()const{return string;}
  operator const char*(){return string;}
  operator char*(){return string;}
private:
  char *string;
  int str_length;
};

inline CString::CString(const char *str)
{
  str_length = strlen(str);
  string = new char[str_length+1];
  strcpy(string,str);
}

inline CString::CString(const CString& str)
{
  str_length = str.length();
  string = new char[str_length+1];
 
  strcpy(string,str.string);
}

inline CString CString::strStr(const CString& str)const
{
  char *tmp_str = NULL;

  if ((tmp_str = strstr(this->string,str.string)) != NULL)
    return CString(tmp_str);
  else
    return CString("");
}

inline CString& CString::toLower()
{
  char *ptr = string;
  
  while (*ptr++ = tolower(*ptr))
    ;

  return *this;
}

inline int CString::isSpace()
{
  char *ptr = string;
  
  while (isspace(*ptr++))
    ;
  return *--ptr == '\000';
}

inline int operator == (const CString& str1, const CString& str2)
{
  return strcmp(str1.string,str2.string) == 0;
}

inline int operator != (const CString& str1, const CString& str2)
{
  return strcmp(str1.string,str2.string) != 0;
}

}//close namespace cxxadt

#endif
  
  

