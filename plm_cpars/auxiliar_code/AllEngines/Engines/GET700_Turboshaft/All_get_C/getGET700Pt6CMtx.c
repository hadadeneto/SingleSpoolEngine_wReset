

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Pt6CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Pt6CMtx[2] = {-1.64943e-01, 8.99197e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Pt6CMtx + i);
};
};