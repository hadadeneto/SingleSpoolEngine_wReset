

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ700PRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ700PRHPTMapMtx[21] = {1.20394e+00, 1.40788e+00, 1.45886e+00, 1.50984e+00, 1.56083e+00, 1.61181e+00, 1.66280e+00, 1.71378e+00, 1.76477e+00, 1.81575e+00, 1.86674e+00, 1.91772e+00, 1.96871e+00, 2.01969e+00, 2.07067e+00, 2.12166e+00, 2.17264e+00, 2.22363e+00, 2.27461e+00, 2.32560e+00, 2.42757e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ700PRHPTMapMtx + i);
};
};