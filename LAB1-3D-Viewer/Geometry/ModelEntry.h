#ifndef LAB1_3D_VIEWER_MODELENTRY_H
#define LAB1_3D_VIEWER_MODELENTRY_H

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

typedef struct InitArgs_
{
	const char *filename;
	LineDrawingFunc lineFunc;
	CleaningFunc cleaningFunc;
} InitArgs;

void fillInitArgs(InitArgs &argStruct, const char *, LineDrawingFunc, CleaningFunc);

ModelEC process(Event, const void *);



#endif //LAB1_3D_VIEWER_MODELENTRY_H
