

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700FNMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700FNMtx[1] = {1.04262e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700FNMtx + i);
};
};