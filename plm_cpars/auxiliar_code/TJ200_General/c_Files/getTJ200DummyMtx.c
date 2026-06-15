


void getTJ200DummyMtx(double *Pointer)
{
int i;
int TotalElem = 9;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200DummyMtx[9] = {0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200DummyMtx + i);
};
};