

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200AMtx(floating *Pointer)
{
int i;
int TotalElem = 4;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200AMtx[4] = {
1.12666e+00, 2.89583e+00,
-5.89596e+00, -1.14983e+01

};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200AMtx + i);
};
};