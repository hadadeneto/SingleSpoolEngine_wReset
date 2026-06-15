


void getTJ1200WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200WcHPCStallMtx[10] = {1.46729e+00, 2.03864e+00, 2.84252e+00, 3.39011e+00, 4.05006e+00, 4.92179e+00, 5.85705e+00, 6.81154e+00, 7.54380e+00, 8.12398e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200WcHPCStallMtx + i);
};
};