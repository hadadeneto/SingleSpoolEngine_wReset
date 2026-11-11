

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200WcFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200WcFANStallMtx[8] = {1.40263e+00, 1.29169e+00, 1.12131e+00, 9.05370e-01, 6.95372e-01, 6.12165e-01, 4.95279e-01, 4.19997e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200WcFANStallMtx + i);
};
};