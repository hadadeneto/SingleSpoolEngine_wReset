

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt21CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt21CMtx[2] = {1.84325e+01, 5.62498e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt21CMtx + i);
};
};