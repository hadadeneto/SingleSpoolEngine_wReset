

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ700NcHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ700NcHPTMapMtx[7] = {3.00732e-01, 3.50854e-01, 4.00976e-01, 4.51098e-01, 5.01220e-01, 5.51342e-01, 1.00244e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ700NcHPTMapMtx + i);
};
};