


void getTJ1200BwmMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200BwmMtx[11] = {0.00000e+00, 3.08673e+02, 1.23463e+03, 2.77778e+03, 4.50000e+03, 6.50000e+03, 9.44444e+03, 1.50000e+04, 1.55493e+03, 1.96795e+03, 2.19269e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200BwmMtx + i);
};
};