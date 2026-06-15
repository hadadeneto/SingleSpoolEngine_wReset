


void getTJ1200WfshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200WfshMtx[1] = {1.70000e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200WfshMtx + i);
};
};