

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt3_KpMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt3_KpMtx[1] = {-0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt3_KpMtx + i);
};
};