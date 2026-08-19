

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGEJ85NcHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GEJ85NcHPTMapMtx[7] = {3.01658e-01, 3.51934e-01, 4.02211e-01, 4.52487e-01, 5.02763e-01, 5.53040e-01, 1.00553e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85NcHPTMapMtx + i);
};
};