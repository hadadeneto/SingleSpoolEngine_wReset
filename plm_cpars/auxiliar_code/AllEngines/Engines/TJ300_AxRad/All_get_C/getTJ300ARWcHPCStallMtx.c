

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARWcHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARWcHPCStallMtx[8] = {4.26440e+01, 3.92711e+01, 3.40911e+01, 2.75259e+01, 2.07185e+01, 1.76810e+01, 1.32510e+01, 1.08538e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARWcHPCStallMtx + i);
};
};