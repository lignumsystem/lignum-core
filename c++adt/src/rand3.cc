#include <iostream.h>
#include <stdlib.h>
#include <time.h>
//	Random numbers:	ran3  	uniform deviates 
namespace cxxadt{

#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

//return uniformally distributed random number [0.0,1.0]
//reinitialize the sequence with any negative integer as 'idum'
double ran3( int* idum)
{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;

	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG;
	ma[inext]=mj;
	return mj*FAC;
}

#undef MBIG
#undef MSEED
#undef MZ
#undef FAC

}//close namespace cxxadt

#ifdef RAND3
int main()
{
  int seed = time(NULL);

  cout << "First sequence" << endl;
  for (int i=0; i < 100; i++){
    cout <<  seed << "  " << ran3(&seed) << endl;
  }

  seed = time(NULL);

  cout << "Second sequence" << endl;
  for (int j=0; j < 100; j++){
    cout <<  seed << "  " << ran3(&seed) << endl;
  }
  
  exit(0);
}
#endif

