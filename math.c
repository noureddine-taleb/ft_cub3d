#include "cub3d.h"

double dist_from_origin(double x, double y) {
	return sqrt(x*x + y*y);
}

void rotate(double *x, double *y, double angle) {
	double _sin = sin(-state.__pa);
	double _cos = cos(-state.__pa);

	double a = *x * _cos - *y * _sin;
	double b = *x * _sin + *y * _cos;
	*x = a;
	*y = b;
}
