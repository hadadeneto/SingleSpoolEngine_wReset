

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700NcFANshContMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700NcFANshContMtx[1] = {3.02297e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700NcFANshContMtx + i);
};
};