

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Ts0Mtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Ts0Mtx[1] = {2.88150e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Ts0Mtx + i);
};
};