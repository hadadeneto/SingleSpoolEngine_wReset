

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Pt3shMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Pt3shMtx[1] = {1.88083e+05};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Pt3shMtx + i);
};
};