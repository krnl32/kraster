#ifndef KRASTER_MATH_UTIL_H
#define KRASTER_MATH_UTIL_H

static inline void swapi(int *x, int *y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

static inline void swapf(float *x, float *y)
{
	float t = *x;
	*x = *y;
	*y = t;
}

#endif
