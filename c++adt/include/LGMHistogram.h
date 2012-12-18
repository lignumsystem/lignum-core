#ifndef LGMHISTOGRAM_H
#define LGMHISTOGRAM_H
#include <vector>

using namespace std;

namespace cxxadt{

  //Histogram
  //Number of classes n
  //Numbering of classes 0, ..., n-1
  //Classes do not need to be evenly spaced; can give in a vector (constructor)
  //If value outside of range (=[vx[0], vx[n]]), goes to fist or last class.
  //vf[i] is frequency in the range [vx[i],vx[i+1]]
  //size.vf() = n, size.vx() = n+1

  class LGMHistogram {
  public:
  LGMHistogram(const vector<double> limits): vx(limits)
    {vf.resize(limits.size() - 1);
      n = static_cast<int>(limits.size()) - 1; }
  LGMHistogram(const int nclasses, const double xmin, const double deltaX): n(nclasses) {
      vx.resize(nclasses + 1);
      vf.resize(nclasses);
      for(int i = 0; i < nclasses; i++) {
	vx[i]= xmin + static_cast<double>(i)*deltaX;
      }
      vx[nclasses] = vx[nclasses-1] + deltaX;
    }

    LGMHistogram& operator += (const LGMHistogram& add_me);
    LGMHistogram& operator = (const LGMHistogram& c);
    int getFrequency(const int i)const;
    int getN() {return n;}
    //Inserts a value to histogram (returns the number of class value
    //belongs to)
    int classify(const double value);
    vector<int> getHistogram() {return vf;}
    vector<double> getLimits() {return vx;}

  private:
    vector<double> vx;   //borders of classes
    vector<int> vf;      //frequencies
    int n;               //no. of classes
  };

}//closing namespace

#endif
