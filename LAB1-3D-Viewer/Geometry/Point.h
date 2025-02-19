#ifndef POINT_H
#define POINT_H

#include <cstdio>

#include "LinearSpace.h"

typedef BASE3d Point;

typedef enum {
    POINT_OK,
    POINT_FORMAT,
    POINT_ARGUMENTS
} PointEc;

PointEc pointFill(FILE *, Point &);

PointEc pointsAverage(const Point *points, int n, Point &result);

void pointMul(Point &, SCALAR);

void pointAdd(Point &pointDest, const Point &point);
void pointSub(Point &, const Point &);

void pointCopy(Point &, const Point &);


#endif //POINT_H
