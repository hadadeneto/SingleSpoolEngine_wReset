

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt6Mtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt6Mtx[1] = {8.71956e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt6Mtx + i);
};
};