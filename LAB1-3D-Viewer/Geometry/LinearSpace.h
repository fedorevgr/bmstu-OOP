#ifndef LINEARSPACE_H
#define LINEARSPACE_H
#include <cmath>

typedef double SCALAR;

typedef struct
{
    SCALAR x, y, z;
} BASE3d;

void set3Scalars(BASE3d& base, SCALAR x, SCALAR y, SCALAR z);

void
matrRotateOX(BASE3d& dst, SCALAR transform);
void
matrRotateOY(BASE3d& dst, SCALAR transform);
void
matrRotateOZ(BASE3d& dst, SCALAR transform);

static inline
double
degreeToRadians(double degree) { return degree / 180 * M_PI; }

#endif //LINEARSPACE_H
