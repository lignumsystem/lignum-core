#include <Gauss.h>

#include <numeric>
#include <vector>
#include <mathsym.h>
#include <math.h>

namespace cxxadt{

  //Before any calls initialize ran3 with seed < 0. 
  double Gauss::operator()(double m, double s, int seed){
    
    static int iset = 0; //flag 
    static double gset = 0;
    double fac,r,v1,v2;
    fac = r = v1 = v2 = 0.0;
    
    //We generate two random numbers v1 and v2
    //so use them alternatively (every other call to gauss
    //regenerates v1 and v2) 
    if (iset == 0){
      do{
	v1 = 2.0*uniform(seed)-1.0; //v1 in range [-1,1]
	v2 = 2.0*uniform(seed)-1.0; //v2 in range [-1,1]
	r  = v1*v1+v2*v2;        //
      }while (r >= 1.0); //repeat until within a unit circle
      fac = sqrt(-2.0*log(r)/r);
      //The Box-Muller transformation
      gset = v1*fac;
      iset = 1; //set the flag
      //Now we have gset in N(0,1)
      //The text book says:
      //If Y = (X-m)/s where X is in N(m,s) then Y is in N(0,1)
      //Thus E(X) = m +s*E(Y) and to return X in N(m,s) we simply return
      return m+s*(v2*fac); 
    }
    else{
      iset = 0;//set the flag
      //we have gset available
      return m+s*gset;
    }
  }
}//closing namespace cxxadt


#ifdef GAUSS

#include <iostream>
using namespace cxxadt;
using namespace std;

template <class T> 
class Square{
public:
  T operator() (T x){return x*x;}
};

int main(int argc, char* argv[])
{
  int init = -1;
  int seed = 0;
  double m = 0.0;
  double sd  = 1.0;
  int n = 100000;
  

  if (argc != 6){
    cout << "Usage: gauss init seed mean stddev sequence_length" << endl;
    return -1;
  }

  init = atoi(argv[argc-5]);
  seed = atoi(argv[argc-4]);
  m =   atof(argv[argc-3]);
  sd =  atof(argv[argc-2]);
  n = atoi(argv[argc-1]);
  vector<double> v(n,0.0); 
  vector<double> v2(n,0.0); 

  Gauss gauss(init);

  //generate n numbers
  for (int i = 0; i < n; i++){
    v[i] = gauss(m,sd,seed); 
    //cout << v[i] << endl;
  }

  //Mean and s^2
  double mean = accumulate(v.begin(),v.end(),0.0)/n;
  transform(v.begin(),v.end(),v2.begin(),Square<double>());
  double s2 = accumulate(v2.begin(),v2.end(),0.0)/n - mean*mean;
  cout << "Mean: " << mean << " s^2: " << s2 << endl;

  //find [-1.96,1.96] and [-1,1] probabilities for N(0,1)
  sort(v.begin(),v.end());
  vector<double>::iterator lower = find_if(v.begin(),v.end(),
					   bind2nd(greater<double>(),
						   -1.96));
  vector<double>::iterator upper = find_if(v.begin(),v.end(),
					   bind2nd(greater<double>(),
						   1.96));
  double l1 = lower - v.begin();
  double l2 = v.end() - upper;

  cout << "[-1.96,1.96] (N(0,1) = 95%): " << (n - (l1 + l2))/n * 100.0<< endl;
  lower = find_if(v.begin(),v.end(),
		  bind2nd(greater<double>(),
			  -1.0));
  upper = find_if(v.begin(),v.end(),
		  bind2nd(greater<double>(),
			  1.0));
  l1 = lower - v.begin();
  l2 = v.end() - upper;
  cout << "[-1,1] (N(0,1) = 68%): " << (n - (l1 + l2))/n * 100.0<< endl;
  
					   
  return 0;
}
#endif
