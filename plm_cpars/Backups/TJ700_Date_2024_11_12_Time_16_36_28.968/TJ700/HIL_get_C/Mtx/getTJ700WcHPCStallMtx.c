


void getTJ700WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ700WcHPCStallMtx[10] = {6.65201e+00, 6.17696e+00, 5.57738e+00, 4.79583e+00, 4.03002e+00, 3.31624e+00, 2.77586e+00, 2.32749e+00, 1.66927e+00, 1.20143e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ700WcHPCStallMtx + i);
};
};