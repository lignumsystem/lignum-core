/**************************************************************************

module A();
module B(int, float);
module C();

Axiom() :
{
  produce A() B(1, 7.5);
}


**************************************************************************/

#include <assert.h>

#include <iostream.h>

#include "lglobals.h"
#include "lstring.h"
#include "succstor.h"
#include "lstriter.h"
#include "dummies.h"

int main()
{
  Lstring string;

  cout << "String in forward mode\n";
  string.Clear(eForward);

/***********
  produce A() B(1, 7.5);
***********/

  cout << "First append: A B\n";
  SuccessorStorage storage;
  storage.Append((ModuleIdType)(A_id));

  storage.Append((ModuleIdType)(B_id)); 
    storage.Append((int)(1)); 
    storage.Append((float)(7.5)); 
  storage.Append((ModuleIdType)(B_id));

  string.Add(storage);

  cout << "Contents of the string:\n";
  {
    LstringIterator iter(string);
    iter.Dump();
  }


  cout << "Add C\n";
  storage.Clear();

/***********
  produce C();
***********/
  storage.Append((ModuleIdType)(C_id));

  string.Add(storage);

  cout << "Contents of the string:\n";
  {
    LstringIterator iter(string);
    iter.Dump();
  }


  cout << "Set string in backward mode\n";

  string.Clear(eBackward);

  cout << "Add C\n";
  storage.Clear();
  storage.Append((ModuleIdType)(C_id));

  string.Add(storage);

  cout << "Contents of the string:\n";
  {
    LstringIterator iter(string);
    iter.Dump();
  }



  cout << "Add A B\n";
  storage.Clear();
  storage.Append((ModuleIdType)(A_id));

  storage.Append((ModuleIdType)(B_id)); 
    storage.Append((int)(1)); 
    storage.Append((float)(7.5)); 
  storage.Append((ModuleIdType)(B_id));

  string.Add(storage);

  cout << "Contents of the string:\n";
  {
    LstringIterator iter(string);
    iter.Dump();
  }


  cout << endl;
}


