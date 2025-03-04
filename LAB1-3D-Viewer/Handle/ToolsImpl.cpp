#include "ToolsI.h"

ModelEC
screenUpdate(const Model& model, const CanvasTools canvasTools)
{
	if (canvasTools.cleaningFunc)
		canvasTools.cleaningFunc(nullptr);

	return modelDraw(model, canvasTools.lineFunc);
}

CanvasTools createCanvasTools(const LineDrawingFunc lineF, const CleaningFunc cleanF)
{
	CanvasTools canvasTools;
	canvasTools.lineFunc = lineF;
	canvasTools.cleaningFunc = cleanF;
	return canvasTools;
}