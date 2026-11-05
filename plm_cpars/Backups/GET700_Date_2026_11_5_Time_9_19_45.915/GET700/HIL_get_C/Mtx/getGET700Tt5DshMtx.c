

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt5DshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt5DshMtx[1] = {3.46092e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt5DshMtx + i);
};
};