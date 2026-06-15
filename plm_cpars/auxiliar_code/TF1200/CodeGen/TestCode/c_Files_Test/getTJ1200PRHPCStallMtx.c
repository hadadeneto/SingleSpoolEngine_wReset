


void getTJ1200PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200PRHPCStallMtx[10] = {1.54097e+00, 1.87040e+00, 2.37858e+00, 2.75466e+00, 3.24012e+00, 3.93533e+00, 4.74953e+00, 5.65338e+00, 6.39672e+00, 7.01644e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200PRHPCStallMtx + i);
};
};