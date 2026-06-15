


void getTJ40PRFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ40PRFANStallMtx[8] = {6.79505e+00, 5.70520e+00, 5.00215e+00, 4.01452e+00, 3.25064e+00, 2.67736e+00, 2.19783e+00, 1.83609e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40PRFANStallMtx + i);
};
};