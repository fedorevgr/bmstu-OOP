#ifndef LAB1_3D_VIEWER_MODELHANDLER_H
#define LAB1_3D_VIEWER_MODELHANDLER_H

#include "Model.h"
#include "ToolsI.h"

typedef enum Event_ {
	INIT,
	REPOS,
	ROTATE,
	SCALE,
	EXIT
} Event;

typedef void (*ErrorHandlerFunc)(ModelEC);

typedef struct Req_
{
	const char *filename;
	BASE3d transform;
	ScreenTools drawTools;
	ErrorHandlerFunc errorHandler;
} Request;

Request composeRequest(const char *, BASE3d, ScreenTools, ErrorHandlerFunc);

static constexpr Request EMPTY_REQ = { nullptr };

void handle(Event, const Request &, ScreenTools, ErrorHandlerFunc);


#endif //LAB1_3D_VIEWER_MODELHANDLER_H
