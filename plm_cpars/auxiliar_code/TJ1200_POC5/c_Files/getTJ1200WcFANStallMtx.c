


void getTJ1200WcFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200WcFANStallMtx[10] = {1.50048e+00, 2.08476e+00, 2.90683e+00, 3.46680e+00, 4.14168e+00, 5.03313e+00, 5.98955e+00, 6.96564e+00, 7.71446e+00, 8.30776e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200WcFANStallMtx + i);
};
};