


void getGEJ85DummyMtx(double *Pointer)
{
int i;
int TotalElem = 18;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85DummyMtx[18] = {0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00, 0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85DummyMtx + i);
};
};