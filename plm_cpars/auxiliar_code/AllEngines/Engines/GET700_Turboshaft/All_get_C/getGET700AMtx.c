

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700AMtx(floating *Pointer)
{
int i;
int TotalElem = 4;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700AMtx[4] = {
-4.73185e-01, 5.46926e-01,
-8.91102e-02, -1.97653e+00

};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700AMtx + i);
};
};