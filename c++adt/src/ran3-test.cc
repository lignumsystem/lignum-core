//Compile: CC ran3-test.cc -IDeveloper/core-model/c++adt/include  -LDeveloper/core-model/c++adt/lib -lcxxadt -lc++ -o ran3-test
#include <vector>
#include <mathsym.h>
#include <iostream>
#include <Uniform.h>
using namespace std;
using namespace cxxadt;
int main()
{
  int seed = -233456;
  int sequence = 1;
  vector<double> v1;
  vector<double> v2;
  
  Uniform *u = new Uniform(seed);
  for (int i = 0; i < 100000; i++){
    v1.push_back((*u)(sequence));
  }

  delete u;
  u = new Uniform(seed);
  for (int i = 0; i < 100000; i++){
    v2.push_back((*u)(sequence));
  }

  for (int i = 0; i < 100000; i++){
    if (v1[i] == v2[i]){
      cout << i << " " << v1[i] << " " << v2[i] <<endl;
    }
  }
  for (int i = 0; i < 100000; i++){
    if (v1[i] != v2[i]){
      cout << "Different: " << i << " " << v1[i] << " " << v2[i] <<endl;
    }
  }
  return 0;
}
