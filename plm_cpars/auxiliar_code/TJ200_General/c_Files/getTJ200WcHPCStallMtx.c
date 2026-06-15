


void getTJ200WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200WcHPCStallMtx[8] = {8.57823e-01, 1.04009e+00, 1.23027e+00, 1.44621e+00, 1.66017e+00, 1.88206e+00, 2.00687e+00, 2.11385e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200WcHPCStallMtx + i);
};
};