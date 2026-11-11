

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RNcHPCMapMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RNcHPCMapMtx[8] = {2.59960e-01, 3.03897e-01, 3.47833e-01, 3.91770e-01, 4.35707e-01, 4.79644e-01, 5.05274e-01, 5.45549e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RNcHPCMapMtx + i);
};
};