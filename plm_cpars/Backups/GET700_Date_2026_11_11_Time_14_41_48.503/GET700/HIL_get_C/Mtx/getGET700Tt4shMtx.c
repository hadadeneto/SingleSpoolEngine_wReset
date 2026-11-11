

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt4shMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt4shMtx[1] = {4.35154e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt4shMtx + i);
};
};