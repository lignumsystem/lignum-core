
#include <CString.h>

namespace cxxadt{

CString& CString::operator=(const CString& str)
{
  delete [] string;

  str_length = str.str_length;
  string = new char[str_length+1];
 
  strcpy(string,str.string);

  return *this;
}

CString& CString::operator+=(const CString& str)
{
  char *string_tmp = new char[this->str_length + str.str_length + 1];
  
  sprintf(string_tmp,"%s%s",string,str.string);

  str_length = this->str_length + str.str_length;
  
  delete string;
  
  string = string_tmp;

  return *this;
}


CString CString::subStr(unsigned int start_pos, unsigned int end_pos)const
{
  int i = start_pos, j= 0;
  char *string_tmp = new char[end_pos - start_pos + 2];

  for (i = start_pos, j = 0; i <= end_pos; i++, j++){
    string_tmp[j] = string[i];
  }
  string_tmp[j] = '\000';

  return CString(string_tmp);
}


ostream& operator<<(ostream& cout,const CString& str)
{
  cout << str.string << flush;
  return cout;
}


CString operator + (const CString& str1, const CString& str2)
{
  CString str_tmp(str1);
  str_tmp += str2;

  return str_tmp;
}

}//close namespace cxxadt

#ifdef CSTRING
#include <iostream>
#include <libc.h>
int main()
{
  CString s1("s1");
  CString s2("s2");
  CString s3("s3");

  s3 = s1 + s2;

  cout << s3 << endl;

  exit(0);
}

#endif
  







