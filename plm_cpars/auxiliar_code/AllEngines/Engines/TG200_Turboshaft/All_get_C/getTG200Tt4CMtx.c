

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt4CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt4CMtx[2] = {-8.97072e-03, 5.53150e-04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt4CMtx + i);
};
};