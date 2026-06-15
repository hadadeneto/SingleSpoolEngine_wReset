


void getGEJ85WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85WcHPCStallMtx[7] = {7.20406e+00, 8.96076e+00, 1.09269e+01, 1.31510e+01, 1.69384e+01, 2.00488e+01, 2.14993e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85WcHPCStallMtx + i);
};
};