

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300WcFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300WcFANStallMtx[12] = {3.94139e+00, 3.79909e+00, 3.64113e+00, 3.20193e+00, 2.93621e+00, 2.68001e+00, 2.23453e+00, 1.84086e+00, 1.46823e+00, 1.06750e+00, 6.70858e-01, 2.64944e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300WcFANStallMtx + i);
};
};