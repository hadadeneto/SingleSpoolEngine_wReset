

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700WcHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700WcHPCStallMtx[8] = {3.50654e+00, 3.22918e+00, 2.80325e+00, 2.26340e+00, 1.70364e+00, 1.45388e+00, 1.08960e+00, 8.92483e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700WcHPCStallMtx + i);
};
};