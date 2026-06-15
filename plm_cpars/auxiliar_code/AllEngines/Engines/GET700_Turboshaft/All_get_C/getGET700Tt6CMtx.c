

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt6CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt6CMtx[2] = {-2.41809e-03, -2.59287e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt6CMtx + i);
};
};