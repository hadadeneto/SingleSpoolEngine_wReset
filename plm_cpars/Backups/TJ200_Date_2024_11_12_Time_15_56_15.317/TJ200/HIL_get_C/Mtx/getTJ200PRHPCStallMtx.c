


void getTJ200PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200PRHPCStallMtx[8] = {4.66667e+00, 3.97710e+00, 3.53226e+00, 2.90736e+00, 2.37707e+00, 1.96204e+00, 1.55605e+00, 1.31104e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200PRHPCStallMtx + i);
};
};