

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Pt6CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Pt6CMtx[2] = {6.00692e+00, 1.71704e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Pt6CMtx + i);
};
};