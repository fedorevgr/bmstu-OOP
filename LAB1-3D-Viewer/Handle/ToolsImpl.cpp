#include "ToolsI.h"

ModelEC
screenUpdate(const Model& model, const ScreenTools screenTools)
{
	if (screenTools.cleaningFunc)
		screenTools.cleaningFunc(nullptr);

	return modelDraw(model, screenTools.lineFunc);
}

ScreenTools composeTools(const LineDrawingFunc lineF, const CleaningFunc cleanF)
{
	ScreenTools canvasTools;
	canvasTools.lineFunc = lineF;
	canvasTools.cleaningFunc = cleanF;
	return canvasTools;
}