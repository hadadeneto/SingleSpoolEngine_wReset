


void getTJ1200PRFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200PRFANStallMtx[10] = {1.52902e+00, 1.85117e+00, 2.34812e+00, 2.71590e+00, 3.19063e+00, 3.87049e+00, 4.66671e+00, 5.55059e+00, 6.27750e+00, 6.88354e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200PRFANStallMtx + i);
};
};