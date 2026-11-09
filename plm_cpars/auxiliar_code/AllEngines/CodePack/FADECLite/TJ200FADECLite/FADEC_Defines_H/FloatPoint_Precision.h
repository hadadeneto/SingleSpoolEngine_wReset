#ifndef FLOATPOINT_PRECISION_H
#define FLOATPOINT_PRECISION_H
//#include <io.h>

/*----------------*/
/* DIGITAL RELAYS */
/*----------------*/

#define DOUBLE_PRECISION 0

#if DOUBLE_PRECISION
typedef double	floating;
#else
typedef float floating;
#endif

#endif /* IO_TYPES_H */
