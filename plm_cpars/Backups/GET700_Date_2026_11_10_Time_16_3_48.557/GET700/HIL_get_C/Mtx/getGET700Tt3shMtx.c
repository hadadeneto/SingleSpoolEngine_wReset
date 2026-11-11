

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt3shMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt3shMtx[1] = {2.91773e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt3shMtx + i);
};
};