


void getTF1200WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200WcHPCStallMtx[10] = {6.59065e-01, 9.15703e-01, 1.27678e+00, 1.52274e+00, 1.81918e+00, 2.21073e+00, 2.63083e+00, 3.05956e+00, 3.38847e+00, 3.64907e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200WcHPCStallMtx + i);
};
};