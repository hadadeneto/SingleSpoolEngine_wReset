

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300PRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300PRHPTMapMtx[21] = {1.22088e+00, 1.44177e+00, 1.49699e+00, 1.55221e+00, 1.60743e+00, 1.66265e+00, 1.71788e+00, 1.77310e+00, 1.82832e+00, 1.88354e+00, 1.93876e+00, 1.99398e+00, 2.04920e+00, 2.10442e+00, 2.15965e+00, 2.21487e+00, 2.27009e+00, 2.32531e+00, 2.38053e+00, 2.43575e+00, 2.54619e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300PRHPTMapMtx + i);
};
};