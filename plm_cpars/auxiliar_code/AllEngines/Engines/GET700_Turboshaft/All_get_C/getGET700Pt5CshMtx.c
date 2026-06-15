

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Pt5CshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Pt5CshMtx[1] = {-2.03238e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Pt5CshMtx + i);
};
};