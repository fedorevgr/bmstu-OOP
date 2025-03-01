#ifndef LAB1_3D_VIEWER_MODELHANDLER_H
#define LAB1_3D_VIEWER_MODELHANDLER_H

#include "Model.h"

typedef void (*CleaningFunc)(void *);
typedef void (*ErrorHandlerFunc)(ModelEC);

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

typedef struct CanvasTools_
{
	LineDrawingFunc lineFunc;
	CleaningFunc cleaningFunc;
} CanvasTools;

CanvasTools createCanvasTools(LineDrawingFunc, CleaningFunc);

static const Request EMPTY_REQ = { nullptr };

void modelHandle(
		Event event,
		Request,
		CanvasTools,
		ErrorHandlerFunc
		);


#endif //LAB1_3D_VIEWER_MODELHANDLER_H
