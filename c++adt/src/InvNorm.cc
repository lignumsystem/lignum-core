///\example InvNorm.cc
///Example for inverse of normal distribution
#include <InvNorm.h>

namespace cxxadt{

  double InvNorm::operator()(const double u)const{
    if(u >= 0.5)
      return inv_norm(u);
    else
      return -inv_norm(1.0-u);
    }

}//closing namespace cxxadt


#ifdef INVNORMMAIN

#include <iostream>
using namespace cxxadt;
using namespace std;

int main(int argc, char* argv[])
{

 std::cout << "Usage: InvNorm(u)" << endl;
 

  //Print out function
  cout << "u      InvNorm(u)" << endl;
  InvNorm q;
  for (double u = 0; u < 1.01; u += 0.1){
    cout << u << " " <<  q(u) << endl;
  }


}
#endif
