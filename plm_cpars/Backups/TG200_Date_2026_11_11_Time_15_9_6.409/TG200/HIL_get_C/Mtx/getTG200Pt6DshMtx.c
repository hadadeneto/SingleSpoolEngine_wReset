

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt6DshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt6DshMtx[1] = {1.99608e+04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt6DshMtx + i);
};
};