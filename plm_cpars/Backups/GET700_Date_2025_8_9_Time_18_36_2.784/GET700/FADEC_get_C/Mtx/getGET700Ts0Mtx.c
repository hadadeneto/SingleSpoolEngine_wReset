

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Ts0Mtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Ts0Mtx[2] = {2.88150e+02, 2.81650e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Ts0Mtx + i);
};
};