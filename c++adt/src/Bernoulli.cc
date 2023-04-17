#include <Bernoulli.h>

#include <numeric>
#include <vector>
#include <mathsym.h>

namespace cxxadt{

  //Probability of success is p
  double Bernoulli::operator()(double p, int seed){
    if (uniform(abs(seed))<p)
      return 1.0;
    else
      return 0.0;
 }
}//closing namespace cxxadt

#ifdef BERNOULLIMAIN
//To test compile with:  g++ -DBERNOULLIMAIN -I../include Bernoulli.cc Uniform.cc 
#include <iostream>
using namespace cxxadt;
using namespace std;

template <class T> 
class Square{
public:
  T operator() (T x){return x*x;}
};

int main()
{
  vector<double> v(10000,0.0);
  Bernoulli b(-1.0);
  
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(0.1,10.0);
  }
  
  double s = accumulate(v.begin(),v.end(),0.0);

  cout << "Success (0.1) " << s/v.size() << " Failure " << 1 - s/v.size() << endl;

  b.init(-1.0);
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(0.2,10.0);
  }
  
  s = accumulate(v.begin(),v.end(),0.0);

  cout << "Success (0.2) " << s/v.size() << " Failure " << 1 - s/v.size() << endl;

  b.init(-1.0);
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(0.4,10.0);
  }
  s = accumulate(v.begin(),v.end(),0.0);
  cout << "Success (0.4) " << s/v.size() << " Failure " << 1 - s/v.size() << endl;

  b.init(-1.0);
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(0.6,10.0);
  }
  s = accumulate(v.begin(),v.end(),0.0);
  cout << "Success (0.6) " << s/v.size() << " Failure " << 1 - s/v.size() << endl;

  b.init(-1.0);
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(0.8,10.0);
  } 
  s = accumulate(v.begin(),v.end(),0.0);
  cout << "Success (0.8) " << s/v.size() << " Failure " << 1 - s/v.size() << endl;

  b.init(-1.0);
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(1.0,10.0);
  }
  s = accumulate(v.begin(),v.end(),0.0);
  cout << "Success (1.0) " << s/v.size()<< " Failure " << 1 - s/v.size()<< endl;

  b.init(-125.0);
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(0.8,10.0);
  } 
  s = accumulate(v.begin(),v.end(),0.0);
  cout << "Success (0.8) " << s/v.size()<< " Failure " << 1 - s/v.size()<< endl;

  b.init(-231.0);
  //Generate random numbers
  for (int i = 0; i < v.size(); i++){
    v[i] = b(0.8,10.0);
  } 
  s = accumulate(v.begin(),v.end(),0.0);
  cout << "Success (0.8) " << s/v.size()<< " Failure " << 1 - s/v.size()<< endl;
  
  return 0;
}
#endif
