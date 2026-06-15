

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt21CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt21CMtx[2] = {2.55393e-03, 1.03459e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt21CMtx + i);
};
};