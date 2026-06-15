

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt5CMtx(floating *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt5CMtx[2] = {-7.24280e-03, 1.34815e-04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt5CMtx + i);
};
};