

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGEJ85DSVec(floating *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GEJ85DSVec[6] = {9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85DSVec + i);
};
};