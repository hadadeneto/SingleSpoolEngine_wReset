

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGEJ85NcVec(floating *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GEJ85NcVec[6] = {5.50000e-01, 6.00000e-01, 7.00000e-01, 8.00000e-01, 9.00000e-01, 9.90000e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85NcVec + i);
};
};