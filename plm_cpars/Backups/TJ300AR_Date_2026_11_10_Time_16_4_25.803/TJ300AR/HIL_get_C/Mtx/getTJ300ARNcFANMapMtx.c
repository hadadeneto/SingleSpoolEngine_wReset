

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARNcFANMapMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARNcFANMapMtx[8] = {5.96639e-01, 6.97479e-01, 7.98319e-01, 8.99160e-01, 1.00000e+00, 1.10084e+00, 1.15966e+00, 1.25210e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARNcFANMapMtx + i);
};
};