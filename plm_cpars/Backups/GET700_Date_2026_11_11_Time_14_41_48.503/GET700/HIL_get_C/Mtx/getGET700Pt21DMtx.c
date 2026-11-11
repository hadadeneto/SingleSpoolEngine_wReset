

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Pt21DMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Pt21DMtx[1] = {1.38652e+06};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Pt21DMtx + i);
};
};