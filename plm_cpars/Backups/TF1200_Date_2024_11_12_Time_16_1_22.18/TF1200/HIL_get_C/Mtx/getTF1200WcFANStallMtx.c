


void getTF1200WcFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200WcFANStallMtx[10] = {1.24839e+01, 1.09781e+01, 1.00670e+01, 9.18861e+00, 7.66127e+00, 6.31151e+00, 5.03393e+00, 3.66000e+00, 2.30009e+00, 9.08380e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200WcFANStallMtx + i);
};
};