

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200FNcMaxContMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200FNcMaxContMtx[1] = {8.67656e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200FNcMaxContMtx + i);
};
};