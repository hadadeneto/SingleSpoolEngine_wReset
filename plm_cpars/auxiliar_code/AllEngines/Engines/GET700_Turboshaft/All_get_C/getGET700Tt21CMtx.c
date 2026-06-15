

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt21CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt21CMtx[2] = {-4.68024e-04, 8.15121e-03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt21CMtx + i);
};
};