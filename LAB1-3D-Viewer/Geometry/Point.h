#ifndef POINT_H
#define POINT_H

#include <cstdio>

typedef double _3DSCALAR_;

typedef struct
{
    _3DSCALAR_ x, y, z;
} _3DBASE_;

typedef _3DBASE_ Point;

typedef enum {
    POINT_OK,
    POINT_FORMAT,
    POINT_ARGUMENTS
} PointEc;

PointEc pointFill(FILE *, Point *);

PointEc pointsAverage(const Point *points, int n, Point *result);

void pointMul(Point *, _3DSCALAR_);

void pointAdd(Point *pointDest, const Point *point);
void pointSub(Point *, const Point *);

void pointCopy(Point *, const Point *);


#endif //POINT_H
