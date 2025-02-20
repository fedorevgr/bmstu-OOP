#include "Point.h"
#include <cstring>


PointEc
pointFill(FILE *file, Point &point)
{
	if (!file)
		return POINT_ARGUMENTS;

	PointEc ec = POINT_OK;

	if (fscanf(file, "%lf%lf%lf", &point.x, &point.y, &point.z) != 3)
		ec = POINT_FORMAT;

	return ec;
}

void
pointCopy(
		Point &__restrict dst,
		const Point &__restrict src
)
{
	dst = src;
}

PointEc
pointsAverage(
		const Point *points,
		const int n,
		Point &result
)
{
	if (!points || n <= 0)
		return POINT_ARGUMENTS;

	Point buffer = { 0 };

	for (int i = 0; i < n; i++)
		pointAdd(buffer, points[i]);
	pointMul(buffer, 1.0 / n);

	result = buffer;

	return POINT_OK;
}

void
pointAdd(
		Point &__restrict pointDest,
		const Point &__restrict point
)
{
	pointDest.x += point.x;
	pointDest.y += point.y;
	pointDest.z += point.z;
}

void
pointSub(
		Point &__restrict pointDest,
		const Point &__restrict pointSrc
)
{
	Point newPoint;
	pointCopy(newPoint, pointSrc);
	pointMul(newPoint, -1);

	pointAdd(pointDest, newPoint);
}

void
pointMul(
		Point &point,
		const SCALAR k
)
{
	point.x *= k;
	point.y *= k;
	point.z *= k;
}

void
pointApplyScale(Point &point, const BASE3d &transform)
{
	point.x *= transform.x;
	point.y *= transform.y;
	point.z *= transform.z;
}

void
pointApplyRotation(Point &point, const BASE3d &transform)
{
	matrRotateOX(point, transform.x);
	matrRotateOY(point, transform.y);
	matrRotateOZ(point, transform.z);
}

void
pointApplyReposition(Point &point, const BASE3d &transform)
{
	point.x += transform.x;
	point.y += transform.y;
	point.z += transform.z;
}
