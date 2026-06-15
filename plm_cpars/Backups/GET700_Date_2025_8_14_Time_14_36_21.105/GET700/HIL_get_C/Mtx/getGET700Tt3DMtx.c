

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt3DMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt3DMtx[1] = {1.56934e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt3DMtx + i);
};
};