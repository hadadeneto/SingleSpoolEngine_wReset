

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt3shMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt3shMtx[1] = {1.88083e+05};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt3shMtx + i);
};
};