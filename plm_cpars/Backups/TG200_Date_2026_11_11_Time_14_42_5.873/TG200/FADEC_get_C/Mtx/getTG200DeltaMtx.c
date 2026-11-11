

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200DeltaMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200DeltaMtx[1] = {1.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200DeltaMtx + i);
};
};