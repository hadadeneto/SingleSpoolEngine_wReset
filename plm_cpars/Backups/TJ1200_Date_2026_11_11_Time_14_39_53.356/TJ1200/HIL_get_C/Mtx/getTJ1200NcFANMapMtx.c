

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ1200NcFANMapMtx(floating *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ1200NcFANMapMtx[10] = {5.01623e-01, 6.01947e-01, 7.02272e-01, 7.52434e-01, 8.02596e-01, 8.52758e-01, 9.02921e-01, 9.53083e-01, 1.00325e+00, 1.05341e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcFANMapMtx + i);
};
};