

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200BMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200BMtx[2] = {
9.05974e+05,
5.30988e+06

};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200BMtx + i);
};
};