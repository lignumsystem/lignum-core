#include <LGMHistogram.h>
//
namespace cxxadt{
    //Adding defined for use with Accumulate.  Both histograms must be
    //identically defined for adding, otherwise nonsense results or a
    //crash
  LGMHistogram& LGMHistogram::operator += (const LGMHistogram& add_me) {
      for(int i = 0; i < n; i++)
	vf[i] += add_me.getFrequency(i);
      
      return *this;
    }

  LGMHistogram& LGMHistogram::operator = (const LGMHistogram& c) {
      vx = c.vx;
      vf = c.vf;
      n = c.n;

      return *this;
    }

  int LGMHistogram::getFrequency(const int i)const {
      if(i < 0)
	return vf[0];
      else if(i > n-1)
	return vf[n-1];
      else
	return vf[i];
    }


    //returns the number of class value belongs to
    int LGMHistogram::classify(const double value) {
      if(value <= vx[0]) { //This is not really necessary. Would
	vf[0]++;           //go to class 0 any way (see below).
	return 0;
      }
      else if(value >= vx[n]) {
	vf[n-1]++;
	return n-1;
      }

      int i;
      for(i = 1; i <= n; i++)
	if(value < vx[i])
	  break;

      vf[i-1]++;
      return i-1;
    }

}//closing namespace

