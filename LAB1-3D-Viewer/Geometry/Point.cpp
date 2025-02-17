#include "Point.h"

PointEc
pointFill(FILE *file, Point *point)
{
    if (!file || !point)
        return POINT_ARGUMENTS;

    PointEc ec = POINT_OK;
    for (int i = 0; i < 3 && ec == POINT_OK; i++) {
        if (fscanf(file, "%lf", &point->x) != 1)
            ec = POINT_FORMAT;
    }
    return ec;
}

PointEc
pointsAverage(
    const Point *points,
    const int n,
    Point *result
)
{
    if (!points || !result || n <= 0)
        return POINT_ARGUMENTS;

    Point buffer = {0};

    for (int i = 0; i < n; i++)
        pointsAdd(&buffer, points + 1);
    pointMul(&buffer, 1.0 / n);

    *result = buffer;

    return POINT_OK;
}

void
pointsAdd(
    Point *__restrict pointDest,
    const Point *__restrict point
) {
    pointDest->x += point->x;
    pointDest->y += point->y;
    pointDest->z += point->z;
}

void
pointMul(
    Point *point,
    const _3DSCALAR_ k
) {
    point->x *= k;
    point->y *= k;
    point->z *= k;
}
