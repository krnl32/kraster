#ifndef KRASTER_MATH_UTIL_H
#define KRASTER_MATH_UTIL_H

static inline void swapi(int *x, int *y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

#endif
