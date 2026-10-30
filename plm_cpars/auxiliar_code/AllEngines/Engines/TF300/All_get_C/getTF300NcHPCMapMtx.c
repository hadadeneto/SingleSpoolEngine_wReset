

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300NcHPCMapMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300NcHPCMapMtx[12] = {4.74302e-01, 5.69162e-01, 6.64023e-01, 7.11453e-01, 7.58883e-01, 8.06314e-01, 8.53744e-01, 9.01174e-01, 9.48604e-01, 9.96034e-01, 1.04346e+00, 1.09089e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300NcHPCMapMtx + i);
};
};