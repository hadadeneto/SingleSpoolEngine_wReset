


void getTF1200AwmMtx(double *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200AwmMtx[12] = {-1.11111e-05, -1.11122e-01, -2.22233e-01, -3.33333e-01, -4.00000e-01, -5.00000e-01, -6.66667e-01, -1.00000e+00, -3.80957e-01, -4.04767e-01, -4.28576e-01, -4.52386e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200AwmMtx + i);
};
};