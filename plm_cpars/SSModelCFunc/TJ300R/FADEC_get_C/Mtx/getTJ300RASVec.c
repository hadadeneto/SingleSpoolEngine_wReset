

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RASVec(floating *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RASVec[6] = {2.00000e+00, 2.00000e+00, 2.00000e+00, 2.00000e+00, 2.00000e+00, 2.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RASVec + i);
};
};