


void getTJ200WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200WcHPCStallMtx[8] = {1.40263e+00, 1.29169e+00, 1.12131e+00, 9.05370e-01, 6.81464e-01, 5.81556e-01, 4.35845e-01, 3.56997e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200WcHPCStallMtx + i);
};
};