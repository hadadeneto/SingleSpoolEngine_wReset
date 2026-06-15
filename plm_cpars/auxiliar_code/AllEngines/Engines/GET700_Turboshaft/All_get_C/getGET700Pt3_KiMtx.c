

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Pt3_KiMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Pt3_KiMtx[1] = {9.32222e-07};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Pt3_KiMtx + i);
};
};