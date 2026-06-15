


void getTJ1200PRHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200PRHPTMapMtx[21] = {1.24304e+00, 1.48609e+00, 1.54685e+00, 1.60761e+00, 1.66837e+00, 1.72913e+00, 1.78989e+00, 1.85065e+00, 1.91141e+00, 1.97217e+00, 2.03293e+00, 2.09369e+00, 2.15445e+00, 2.21522e+00, 2.27598e+00, 2.33674e+00, 2.39750e+00, 2.45826e+00, 2.51902e+00, 2.57978e+00, 2.70130e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200PRHPTMapMtx + i);
};
};