

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt21CshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt21CshMtx[1] = {2.91773e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt21CshMtx + i);
};
};