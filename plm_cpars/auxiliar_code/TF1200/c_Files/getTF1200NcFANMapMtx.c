


void getTF1200NcFANMapMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200NcFANMapMtx[10] = {4.54545e-01, 5.45455e-01, 6.36364e-01, 6.81818e-01, 7.27273e-01, 7.72727e-01, 8.18182e-01, 8.63636e-01, 9.09091e-01, 9.54545e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200NcFANMapMtx + i);
};
};