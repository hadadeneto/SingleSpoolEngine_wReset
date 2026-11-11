

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt4CshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt4CshMtx[1] = {4.27295e+04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt4CshMtx + i);
};
};