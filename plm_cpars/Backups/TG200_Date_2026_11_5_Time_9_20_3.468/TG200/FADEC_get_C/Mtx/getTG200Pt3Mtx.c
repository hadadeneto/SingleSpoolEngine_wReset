

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt3Mtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt3Mtx[1] = {8.61304e+05};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt3Mtx + i);
};
};