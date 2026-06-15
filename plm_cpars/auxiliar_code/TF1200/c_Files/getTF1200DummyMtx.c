


void getTF1200DummyMtx(double *Pointer)
{
int i;
int TotalElem = 16;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200DummyMtx[16] = {0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200DummyMtx + i);
};
};