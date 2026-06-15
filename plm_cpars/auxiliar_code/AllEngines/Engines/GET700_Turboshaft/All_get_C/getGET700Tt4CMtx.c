

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt4CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt4CMtx[2] = {-3.16200e-03, -2.85304e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt4CMtx + i);
};
};