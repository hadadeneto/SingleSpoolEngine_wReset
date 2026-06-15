

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700N_KishMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700N_KishMtx[12] = {5.42599e-08, 7.26980e-08, 2.06195e-07, 3.39155e-07, 4.76684e-07, 6.08570e-07, 7.45004e-07, 8.80886e-07, 1.01118e-06, 1.14095e-06, 1.29022e-06, 1.41891e-06};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700N_KishMtx + i);
};
};