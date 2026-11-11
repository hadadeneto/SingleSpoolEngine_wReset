

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700PRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700PRHPTMapMtx[21] = {1.30041e+00, 1.60082e+00, 1.67592e+00, 1.75102e+00, 1.82612e+00, 1.90123e+00, 1.97633e+00, 2.05143e+00, 2.12653e+00, 2.20164e+00, 2.27674e+00, 2.35184e+00, 2.42694e+00, 2.50204e+00, 2.57715e+00, 2.65225e+00, 2.72735e+00, 2.80245e+00, 2.87756e+00, 2.95266e+00, 3.10286e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700PRHPTMapMtx + i);
};
};