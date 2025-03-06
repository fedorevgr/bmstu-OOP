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
	Event event;
	const char *filename;
	BASE3d transform;
	ScreenTools drawTools;
	ErrorHandlerFunc errorHandler;
} Request;

Request composeRequest(Event, const char *, const BASE3d &, const ScreenTools &, ErrorHandlerFunc);

static constexpr Request EMPTY_REQ = { EXIT };

void handle(const Request &);


#endif //LAB1_3D_VIEWER_MODELHANDLER_H
