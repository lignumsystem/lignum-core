/// \file LGMHistogram.h
/// \brief Histogram generator
#ifndef LGMHISTOGRAM_H
#define LGMHISTOGRAM_H
#include <vector>

using namespace std;

namespace cxxadt{

  ///\brief Histogram generator
  ///
  ///Numbering of classes 0, ..., n-1.
  ///Classes do not need to be evenly spaced; can be given in a vector (constructor)
  ///If value outside of range (=[vx[0], vx[n]]), goes to fist or last class.
  ///vf[i] is frequency in the range [vx[i],vx[i+1]]
  ///size.vf() = n, size.vx() = n+1
  class LGMHistogram {
  public:
  ///\brief Constructor with predefined classes
  ///
  ///Classses do need to be evenly spaced
  ///\param limits Predefined classes
  LGMHistogram(const vector<double> limits): vx(limits)
    {vf.resize(limits.size() - 1);
      n = static_cast<int>(limits.size()) - 1; }
  ///\brief Constructor with \p nclasses
  ///\param nclasses Number of classes
  ///\param xmin Lower limit for class values
  ///\param deltaX Class size increment
  ///\post Classes are evenly spaced with \p deltaX
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
    ///\brief Inserts a value to histogram
    ///\param value Value to be insterted
    ///\return Number of class values \p value belongs to
    int classify(const double value);
    ///\brief Histogram values
    ///\retval vf Vector of histogram values
    vector<int> getHistogram() {return vf;}
    ///\brief Histogram classes
    ///\retval vx Vector of histogram classes
    vector<double> getLimits() {return vx;}
  private:
    vector<double> vx;   ///< Borders (upper limit) of classes
    vector<int> vf;      ///< Frequencies
    int n;               ///< Number of classes
  };

}//closing namespace

#endif
