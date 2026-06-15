


void getGEJ85PRHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85PRHPTMapMtx[21] = {1.33742e+00, 1.67484e+00, 1.75920e+00, 1.84356e+00, 1.92791e+00, 2.01227e+00, 2.09662e+00, 2.18098e+00, 2.26533e+00, 2.34969e+00, 2.43404e+00, 2.51840e+00, 2.60275e+00, 2.68711e+00, 2.77147e+00, 2.85582e+00, 2.94018e+00, 3.02453e+00, 3.10889e+00, 3.19324e+00, 3.36195e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85PRHPTMapMtx + i);
};
};