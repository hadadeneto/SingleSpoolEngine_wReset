

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RNcFANMapMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RNcFANMapMtx[8] = {6.34332e-01, 7.41544e-01, 8.48755e-01, 9.55966e-01, 1.06318e+00, 1.17039e+00, 1.23293e+00, 1.33120e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RNcFANMapMtx + i);
};
};