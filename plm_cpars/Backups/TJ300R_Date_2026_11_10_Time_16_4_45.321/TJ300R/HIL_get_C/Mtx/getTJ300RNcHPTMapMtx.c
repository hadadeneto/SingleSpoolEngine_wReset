

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RNcHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RNcHPTMapMtx[7] = {2.99670e-01, 3.49615e-01, 3.99560e-01, 4.49505e-01, 4.99450e-01, 5.49395e-01, 9.98901e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RNcHPTMapMtx + i);
};
};