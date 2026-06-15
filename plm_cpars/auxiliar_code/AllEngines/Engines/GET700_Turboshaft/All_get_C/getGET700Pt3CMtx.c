

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Pt3CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Pt3CMtx[2] = {-1.88071e+00, 2.57479e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Pt3CMtx + i);
};
};