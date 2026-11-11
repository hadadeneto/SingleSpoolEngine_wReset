

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARWcFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARWcFANStallMtx[8] = {2.85900e+01, 2.63286e+01, 2.28558e+01, 1.84543e+01, 1.41738e+01, 1.24778e+01, 1.00953e+01, 8.56084e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARWcFANStallMtx + i);
};
};