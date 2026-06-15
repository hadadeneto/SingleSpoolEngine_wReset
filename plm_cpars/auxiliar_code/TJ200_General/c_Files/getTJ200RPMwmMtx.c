


void getTJ200RPMwmMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200RPMwmMtx[10] = {0.00000e+00, 8.33333e+02, 1.66667e+03, 2.50000e+03, 4.50000e+03, 6.50000e+03, 8.50000e+03, 1.05000e+04, 2.85714e+03, 3.21429e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200RPMwmMtx + i);
};
};