

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt6DMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt6DMtx[1] = {7.06327e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt6DMtx + i);
};
};