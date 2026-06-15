

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700WcFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700WcFANStallMtx[8] = {3.50654e+00, 3.22918e+00, 2.80325e+00, 2.26340e+00, 1.73841e+00, 1.53040e+00, 1.23818e+00, 1.04998e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700WcFANStallMtx + i);
};
};