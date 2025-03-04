#ifndef LAB1_3D_VIEWER_MODELHANDLER_H
#define LAB1_3D_VIEWER_MODELHANDLER_H

#include "Model.h"
#include "DrawInterface.h"

typedef enum Event_ {
	INIT,
	REPOS,
	ROTATE,
	SCALE,
	EXIT
} Event;

typedef struct Req_
{
	const char *filename;
	BASE3d transform;
} Request;

static const Request EMPTY_REQ = { nullptr };

void handle(Event, Request, CanvasTools, ErrorHandlerFunc);


#endif //LAB1_3D_VIEWER_MODELHANDLER_H
