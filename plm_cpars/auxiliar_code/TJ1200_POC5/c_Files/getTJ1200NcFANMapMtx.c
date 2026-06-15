


void getTJ1200NcFANMapMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200NcFANMapMtx[10] = {5.21223e-01, 6.25467e-01, 7.29712e-01, 7.81834e-01, 8.33956e-01, 8.86079e-01, 9.38201e-01, 9.90323e-01, 1.04245e+00, 1.09457e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcFANMapMtx + i);
};
};