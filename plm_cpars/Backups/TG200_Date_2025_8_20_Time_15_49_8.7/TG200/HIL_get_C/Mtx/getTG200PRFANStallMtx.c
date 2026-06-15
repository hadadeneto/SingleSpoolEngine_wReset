

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200PRFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200PRFANStallMtx[8] = {1.08214e+01, 8.97436e+00, 7.78284e+00, 6.10900e+00, 4.81438e+00, 3.84279e+00, 3.03008e+00, 2.41700e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200PRFANStallMtx + i);
};
};