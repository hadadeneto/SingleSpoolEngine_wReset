


void getGEJ85ThetaMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85ThetaMtx[10] = {1.00000e+00, 1.00200e+00, 1.00799e+00, 1.01797e+00, 1.03195e+00, 1.04991e+00, 1.07187e+00, 1.09781e+00, 1.12809e+00, 1.14458e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85ThetaMtx + i);
};
};