

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700N_KpshMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700N_KpshMtx[12] = {3.58785e-06, 3.58680e-06, 3.57906e-06, 3.57134e-06, 3.56177e-06, 3.55359e-06, 3.54249e-06, 3.53036e-06, 3.52124e-06, 3.51216e-06, 3.48274e-06, 3.47169e-06};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700N_KpshMtx + i);
};
};