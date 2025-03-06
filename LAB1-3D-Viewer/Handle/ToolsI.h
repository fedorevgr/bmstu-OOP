#ifndef LAB1_3D_VIEWER_DRAWINTERFACE_H
#define LAB1_3D_VIEWER_DRAWINTERFACE_H

#include "Model.h"

typedef void (*CleaningFunc)(void *);

typedef struct ScreenTools_
{
	LineDrawingFunc lineFunc;
	void *lineFuncArgs;
	CleaningFunc cleaningFunc;
	void *cleaningFuncArgs;
} ScreenTools;

ScreenTools composeTools(LineDrawingFunc, void *, CleaningFunc, void *);
ModelEC screenUpdate(const Model& model, ScreenTools screenTools);


#endif //LAB1_3D_VIEWER_DRAWINTERFACE_H
