

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700DummyMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700DummyMtx[1] = {0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700DummyMtx + i);
};
};