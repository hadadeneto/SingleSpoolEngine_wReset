

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ40WcFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ40WcFANStallMtx[8] = {6.87156e-01, 6.32804e-01, 5.49336e-01, 4.43545e-01, 3.40666e-01, 2.99903e-01, 2.42640e-01, 2.05759e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40WcFANStallMtx + i);
};
};