


void getTF1200PRFANStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200PRFANStallMtx[10] = {9.52080e-01, 9.81589e-01, 1.02667e+00, 1.08603e+00, 1.15654e+00, 1.23768e+00, 1.31609e+00, 1.34784e+00, 1.37372e+00, 1.41757e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200PRFANStallMtx + i);
};
};