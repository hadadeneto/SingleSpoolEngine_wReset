

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700BMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700BMtx[2] = {
7.27341e+04,
2.22607e+05

};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700BMtx + i);
};
};