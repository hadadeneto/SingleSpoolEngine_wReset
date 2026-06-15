

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt21shMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt21shMtx[1] = {8.79096e+04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt21shMtx + i);
};
};