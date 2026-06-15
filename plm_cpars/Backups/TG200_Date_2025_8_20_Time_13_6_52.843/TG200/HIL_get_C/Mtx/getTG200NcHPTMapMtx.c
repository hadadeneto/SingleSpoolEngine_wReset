

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200NcHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200NcHPTMapMtx[7] = {3.05155e-01, 3.56014e-01, 4.06873e-01, 4.57732e-01, 5.08592e-01, 5.59451e-01, 1.01718e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200NcHPTMapMtx + i);
};
};