#ifndef POINT_H
#define POINT_H

#include <cstdio>

#define _3DBASE_ base_3d__
#define _3DSCALAR_ double

typedef struct _3DBASE_
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
void pointsAdd(Point *, const Point *);


#endif //POINT_H
