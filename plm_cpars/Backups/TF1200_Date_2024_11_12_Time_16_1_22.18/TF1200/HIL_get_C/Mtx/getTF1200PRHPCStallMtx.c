


void getTF1200PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200PRHPCStallMtx[10] = {5.84374e+00, 5.34481e+00, 4.74636e+00, 4.01869e+00, 3.36319e+00, 2.80348e+00, 2.41264e+00, 2.10987e+00, 1.70075e+00, 1.43552e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200PRHPCStallMtx + i);
};
};