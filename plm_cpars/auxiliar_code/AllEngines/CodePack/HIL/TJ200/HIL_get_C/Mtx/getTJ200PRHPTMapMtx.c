

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ200PRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ200PRHPTMapMtx[21] = {1.17386e+00, 1.34771e+00, 1.39117e+00, 1.43464e+00, 1.47810e+00, 1.52157e+00, 1.56503e+00, 1.60849e+00, 1.65196e+00, 1.69542e+00, 1.73888e+00, 1.78235e+00, 1.82581e+00, 1.86928e+00, 1.91274e+00, 1.95620e+00, 1.99967e+00, 2.04313e+00, 2.08659e+00, 2.13006e+00, 2.21699e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200PRHPTMapMtx + i);
};
};