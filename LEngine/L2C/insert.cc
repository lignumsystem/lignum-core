#include <list>

using namespace std;

int main()
{
  list<int> ls(1,1);
  list<int>::iterator itr;

  itr = ls.begin();
  ls.insert(itr,2);
  ls.insert(itr,3);
  ls.insert(itr,4);
  
  copy(itr,ls.end(),ostream_iterator<int>(cout," "));
  cout << endl;
  copy(ls.begin(),ls.end(),ostream_iterator<int>(cout," "));
  cout << endl;

  return 0;
}
