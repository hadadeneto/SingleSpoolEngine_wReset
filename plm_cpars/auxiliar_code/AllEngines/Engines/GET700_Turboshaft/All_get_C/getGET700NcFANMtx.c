

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700NcFANMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700NcFANMtx[1] = {9.99999e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700NcFANMtx + i);
};
};