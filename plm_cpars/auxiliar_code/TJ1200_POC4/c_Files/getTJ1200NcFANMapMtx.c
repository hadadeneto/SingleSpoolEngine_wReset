


void getTJ1200NcFANMapMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200NcFANMapMtx[10] = {5.25133e-01, 6.30160e-01, 7.35186e-01, 7.87700e-01, 8.40213e-01, 8.92726e-01, 9.45240e-01, 9.97753e-01, 1.05027e+00, 1.10278e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcFANMapMtx + i);
};
};