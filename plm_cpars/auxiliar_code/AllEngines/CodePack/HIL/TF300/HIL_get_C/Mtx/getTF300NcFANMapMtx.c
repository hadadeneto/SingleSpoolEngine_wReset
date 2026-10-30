

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300NcFANMapMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300NcFANMapMtx[12] = {3.00000e-01, 4.00000e-01, 5.00000e-01, 6.00000e-01, 7.00000e-01, 8.00000e-01, 9.00000e-01, 9.50000e-01, 1.00000e+00, 1.10000e+00, 1.20000e+00, 1.30000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300NcFANMapMtx + i);
};
};