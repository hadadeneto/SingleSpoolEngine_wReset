


void getGEJ85DeltaMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85DeltaMtx[10] = {1.00000e+00, 1.00702e+00, 1.02828e+00, 1.06443e+00, 1.11656e+00, 1.18622e+00, 1.27551e+00, 1.38711e+00, 1.52588e+00, 1.60549e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85DeltaMtx + i);
};
};