


void getTJ1200PRHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200PRHPTMapMtx[21] = {1.24735e+00, 1.49470e+00, 1.55654e+00, 1.61837e+00, 1.68021e+00, 1.74205e+00, 1.80389e+00, 1.86572e+00, 1.92756e+00, 1.98940e+00, 2.05124e+00, 2.11308e+00, 2.17491e+00, 2.23675e+00, 2.29859e+00, 2.36043e+00, 2.42226e+00, 2.48410e+00, 2.54594e+00, 2.60778e+00, 2.73145e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200PRHPTMapMtx + i);
};
};