

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700WfMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700WfMtx[1] = {9.99995e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700WfMtx + i);
};
};