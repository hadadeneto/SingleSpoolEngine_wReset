

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300PRFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300PRFANStallMtx[12] = {1.89177e+00, 1.76412e+00, 1.63648e+00, 1.50883e+00, 1.43862e+00, 1.37593e+00, 1.27865e+00, 1.20505e+00, 1.14610e+00, 1.09430e+00, 1.05489e+00, 1.02676e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300PRFANStallMtx + i);
};
};