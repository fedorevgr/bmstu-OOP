#ifndef LAB1_3D_VIEWER_DRAWINTERFACE_H
#define LAB1_3D_VIEWER_DRAWINTERFACE_H

#include "Model.h"

typedef void (*CleaningFunc)(void *);

typedef struct CanvasTools_
{
	LineDrawingFunc lineFunc;
	CleaningFunc cleaningFunc;
} CanvasTools;

CanvasTools createCanvasTools(LineDrawingFunc, CleaningFunc);
ModelEC screenUpdate(const Model& model, CanvasTools canvasTools);


#endif //LAB1_3D_VIEWER_DRAWINTERFACE_H
