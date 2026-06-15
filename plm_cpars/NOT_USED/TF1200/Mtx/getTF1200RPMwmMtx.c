


void getTF1200RPMwmMtx(double *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200RPMwmMtx[12] = {0.00000e+00, 8.33333e+02, 1.66667e+03, 2.50000e+03, 4.50000e+03, 6.50000e+03, 8.50000e+03, 1.05000e+04, 2.85714e+03, 3.03571e+03, 3.21429e+03, 3.39286e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200RPMwmMtx + i);
};
};