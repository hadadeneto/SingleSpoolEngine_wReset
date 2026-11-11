

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Pt3DshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Pt3DshMtx[1] = {1.01259e+05};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Pt3DshMtx + i);
};
};