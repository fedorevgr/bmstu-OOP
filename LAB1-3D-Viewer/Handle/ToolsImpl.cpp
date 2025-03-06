#include "ToolsI.h"

ModelEC
screenUpdate(const Model& model, const ScreenTools screenTools)
{
	if (screenTools.cleaningFunc)
		screenTools.cleaningFunc(screenTools.lineFuncArgs);

	return modelDraw(model, screenTools.lineFunc, screenTools.lineFuncArgs);
}

ScreenTools composeTools(
		const LineDrawingFunc lineF, void *lineFArgs,
		const CleaningFunc cleanF, void *cleanFArgs)
{
	ScreenTools canvasTools;

	canvasTools.lineFunc = lineF;
	canvasTools.lineFuncArgs = lineFArgs;
	canvasTools.cleaningFunc = cleanF;
	canvasTools.cleaningFuncArgs = cleanFArgs;

	return canvasTools;
}