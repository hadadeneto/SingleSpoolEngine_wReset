

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300WcHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300WcHPCStallMtx[12] = {1.69710e+00, 1.61745e+00, 1.54070e+00, 1.43067e+00, 1.29180e+00, 1.11078e+00, 9.33407e-01, 7.68086e-01, 6.42927e-01, 5.39078e-01, 3.86625e-01, 2.78268e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300WcHPCStallMtx + i);
};
};