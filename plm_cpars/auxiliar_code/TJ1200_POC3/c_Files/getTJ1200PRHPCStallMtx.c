


void getTJ1200PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200PRHPCStallMtx[10] = {1.58237e+00, 1.93701e+00, 2.48408e+00, 2.88894e+00, 3.41155e+00, 4.15997e+00, 5.03648e+00, 6.00950e+00, 6.80972e+00, 7.47687e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200PRHPCStallMtx + i);
};
};