#ifndef LAB1_3D_VIEWER_MODELHANDLER_H
#define LAB1_3D_VIEWER_MODELHANDLER_H

#include "Model.h"

typedef enum Event_ {
	INIT,
	REPOS,
	ROTATE,
	SCALE,
	EXIT
} Event;

typedef union Req_
{
	const char *filename;
	BASE3d transform;
} Request;

static const Request EMPTY_REQ = { nullptr };

typedef void (*CleaningFunc)(void *);
typedef void (*ErrorHandlerFunc)(ModelEC);

void modelHandle(
		Event event,
		Request,
		LineDrawingFunc,
		CleaningFunc,
		ErrorHandlerFunc);


#endif //LAB1_3D_VIEWER_MODELHANDLER_H
