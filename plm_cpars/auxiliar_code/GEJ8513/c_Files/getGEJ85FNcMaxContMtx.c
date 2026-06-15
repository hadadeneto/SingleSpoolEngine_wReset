


void getGEJ85FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85FNcMaxContMtx[10] = {1.19862e+04, 1.13676e+04, 1.08446e+04, 1.04142e+04, 1.00689e+04, 9.79847e+03, 9.59022e+03, 9.43108e+03, 9.31378e+03, 9.26127e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85FNcMaxContMtx + i);
};
};