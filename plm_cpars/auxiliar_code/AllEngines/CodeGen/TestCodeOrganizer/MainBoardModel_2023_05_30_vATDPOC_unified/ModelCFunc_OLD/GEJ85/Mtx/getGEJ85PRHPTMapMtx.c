


void getGEJ85PRHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85PRHPTMapMtx[21] = {1.20216e+00, 1.40432e+00, 1.45486e+00, 1.50540e+00, 1.55594e+00, 1.60648e+00, 1.65702e+00, 1.70756e+00, 1.75810e+00, 1.80864e+00, 1.85918e+00, 1.90972e+00, 1.96026e+00, 2.01080e+00, 2.06135e+00, 2.11189e+00, 2.16243e+00, 2.21297e+00, 2.26351e+00, 2.31405e+00, 2.41513e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85PRHPTMapMtx + i);
};
};