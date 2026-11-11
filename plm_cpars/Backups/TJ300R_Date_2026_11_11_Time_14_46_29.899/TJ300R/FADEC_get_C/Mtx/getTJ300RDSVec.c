

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RDSVec(floating *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RDSVec[6] = {9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RDSVec + i);
};
};