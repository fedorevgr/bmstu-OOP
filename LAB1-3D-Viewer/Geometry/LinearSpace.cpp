#include "LinearSpace.h"

void
set3Scalars
		(
				BASE3d& base,
				const SCALAR x, const SCALAR y, const SCALAR z
		)
{
	base.x = x;
	base.y = y;
	base.z = z;
}

void
matrRotateOX(BASE3d& dst, const SCALAR transform)
{
	/*	OX
	*		1	 0   0
	*	    0 	 cos sin
	*		0	-sin cos
	*/
	BASE3d copy = dst;
	set3Scalars(dst,
			copy.x,
			copy.y * cos(transform) - copy.z * sin(transform),
			copy.y * sin(transform) + copy.z * cos(transform)
	);
}

void
matrRotateOY(BASE3d& dst, const SCALAR transform)
{
	BASE3d copy = dst;
	set3Scalars(dst,
			copy.x * cos(transform) - copy.z * sin(transform),
			copy.y,
			copy.x * sin(transform) + copy.z * cos(transform)
	);
}

void
matrRotateOZ(BASE3d& dst, const SCALAR transform)
{
	BASE3d copy = dst;
	set3Scalars(dst,
			copy.x * cos(transform) - copy.y * sin(transform),
			copy.x * sin(transform) + copy.y * cos(transform),
			copy.z
	);
}

