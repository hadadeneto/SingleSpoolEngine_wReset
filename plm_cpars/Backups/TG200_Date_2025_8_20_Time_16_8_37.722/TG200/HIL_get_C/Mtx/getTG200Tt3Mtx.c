

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt3Mtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt3Mtx[1] = {5.69432e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt3Mtx + i);
};
};