

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt6DMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt6DMtx[1] = {1.79527e+04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt6DMtx + i);
};
};