//#include "nr3.h"
#include "calendar.h"
#include "moment.h"

Int main(void)
{
  const Int NTOT=20;
  Int i,jd,nph=2;
  Doub frac,ave,vrnce;
  VecDoub data(NTOT);
  for (i=0;i<NTOT;i++) {
    flmoon(i,nph,jd,frac);
    data[i]=jd;
  }
  avevar(data,ave,vrnce);
  cout << "Average = " << setw(12) << ave;
  cout << " Variance = " << setw(13) << vrnce << endl;
  return 0;
}
