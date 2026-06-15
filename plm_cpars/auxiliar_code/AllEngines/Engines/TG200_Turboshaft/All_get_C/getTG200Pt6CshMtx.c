

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt6CshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt6CshMtx[1] = {-2.03238e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt6CshMtx + i);
};
};