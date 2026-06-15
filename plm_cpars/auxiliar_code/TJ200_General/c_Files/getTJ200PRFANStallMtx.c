


void getTJ200PRFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200PRFANStallMtx[8] = {1.48167e+00, 1.70153e+00, 1.99490e+00, 2.37275e+00, 2.84990e+00, 3.42999e+00, 3.85972e+00, 4.50651e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200PRFANStallMtx + i);
};
};