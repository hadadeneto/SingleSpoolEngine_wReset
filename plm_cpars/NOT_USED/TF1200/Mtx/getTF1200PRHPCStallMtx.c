


void getTF1200PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200PRHPCStallMtx[10] = {1.43554e+00, 1.70077e+00, 2.10991e+00, 2.41270e+00, 2.80355e+00, 3.36327e+00, 4.01880e+00, 4.74649e+00, 5.34496e+00, 5.84391e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200PRHPCStallMtx + i);
};
};