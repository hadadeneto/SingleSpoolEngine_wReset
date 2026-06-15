


void getTJ1200DummyMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200DummyMtx[10] = {0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200DummyMtx + i);
};
};