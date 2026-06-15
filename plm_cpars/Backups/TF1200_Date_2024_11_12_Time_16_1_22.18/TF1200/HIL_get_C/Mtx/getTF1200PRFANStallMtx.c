


void getTF1200PRFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200PRFANStallMtx[10] = {2.20223e+00, 1.96112e+00, 1.82850e+00, 1.71010e+00, 1.52633e+00, 1.38733e+00, 1.27596e+00, 1.17813e+00, 1.10368e+00, 1.05055e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200PRFANStallMtx + i);
};
};