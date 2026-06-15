

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700DeltaMtx(floating *Pointer)
{
int i;
int TotalElem = 4;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700DeltaMtx[4] = {
1.00000e+00, 1.00702e+00,
8.89808e-01, 8.96052e-01

};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700DeltaMtx + i);
};
};