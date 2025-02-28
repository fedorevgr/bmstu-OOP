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

static const void *NO_ARG = nullptr;

typedef void (*CleaningFunc)(void *);
typedef void (*ErrorHandlerFunc)(ModelEC);

void modelHandle(
		Event event,
		const void *arg,
		LineDrawingFunc,
		CleaningFunc,
		ErrorHandlerFunc);


#endif //LAB1_3D_VIEWER_MODELHANDLER_H
