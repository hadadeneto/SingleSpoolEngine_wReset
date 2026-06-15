


void getGEJ85PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85PRHPCStallMtx[7] = {1.27215e+00, 1.73769e+00, 2.22450e+00, 2.72578e+00, 3.06952e+00, 5.06745e+00, 6.21625e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85PRHPCStallMtx + i);
};
};