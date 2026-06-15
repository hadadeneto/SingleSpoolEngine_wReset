


void getGEJ85PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85PRHPCStallMtx[7] = {8.37934e+00, 7.89603e+00, 6.42094e+00, 4.55898e+00, 3.59945e+00, 3.02797e+00, 2.54677e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85PRHPCStallMtx + i);
};
};