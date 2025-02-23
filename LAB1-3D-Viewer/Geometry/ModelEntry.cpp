#include "ModelEntry.h"

void fillInitArgs(
		InitArgs &argStruct,
		const char *fName, LineDrawingFunc func, CleaningFunc clean, ErrorHandlingFunc errHandler)
{
	argStruct.lineFunc = func;
	argStruct.filename = fName;
	argStruct.cleaningFunc = clean;
	argStruct.errorHandler = errHandler;
}

ModelEC
process(const Event event, const void *arg) {
	static Model model;
	static LineDrawingFunc drawingFunc;
	static CleaningFunc cleaningFunc;
	static ErrorHandlingFunc errHandler;

	BASE3d *newPos, *newRotation, *newScale;

	ModelEC modelEc = MODEL_OK;

	switch (event) {
	case INIT:
		modelEc = initModel(((const InitArgs *) arg)->filename, model);
		drawingFunc = ((const InitArgs *) arg)->lineFunc;
		cleaningFunc = ((const InitArgs *) arg)->cleaningFunc;
		errHandler = ((const InitArgs *) arg)->errorHandler;
		break;
	case REPOS:
		newPos = (BASE3d *) arg;
		modelSetPos(model, *newPos);
		break;
	case ROTATE:
		newRotation = (BASE3d *) arg;
		modelSetRot(model, *newRotation);
		break;
	case SCALE:
		newScale = (BASE3d *) arg;
		modelSetScale(model, *newScale);
		break;
	case EXIT:
		modelFree(model);
		break;
	}

	if (event != EXIT && modelEc == MODEL_OK)
	{
		cleaningFunc(nullptr);
		modelDraw(model, drawingFunc);
	}

	errHandler(modelEc, nullptr);

	return modelEc;
}
