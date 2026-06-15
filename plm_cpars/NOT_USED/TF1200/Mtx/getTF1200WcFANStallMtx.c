


void getTF1200WcFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200WcFANStallMtx[10] = {4.12024e+00, 5.39420e+00, 6.69282e+00, 7.97488e+00, 9.19988e+00, 1.03862e+01, 1.13887e+01, 1.17647e+01, 1.20608e+01, 1.25431e+01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200WcFANStallMtx + i);
};
};