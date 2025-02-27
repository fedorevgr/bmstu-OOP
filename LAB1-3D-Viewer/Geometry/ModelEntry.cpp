#include "ModelEntry.h"

void fillInitArgs(
		InitArgs &argStruct,
		const char *fName, LineDrawingFunc func, CleaningFunc clean)
{
	argStruct.lineFunc = func;
	argStruct.filename = fName;
	argStruct.cleaningFunc = clean;
}

static inline
ModelEC
checkInitArgs(const InitArgs *iArgs)
{
	ModelEC ec = MODEL_OK;
	if (iArgs->cleaningFunc == nullptr || iArgs->lineFunc == nullptr)
		ec = MODEL_ARG_ERROR;
	return ec;
}

ModelEC
process(const Event event, const void *arg) {
	if (event == INIT && checkInitArgs((const InitArgs *) arg) != MODEL_OK)
		return MODEL_ARG_ERROR;

	static Model model;
	static LineDrawingFunc drawingFunc;
	static CleaningFunc cleaningFunc;

	BASE3d *newPos, *newRotation, *newScale;

	ModelEC modelEc = MODEL_OK;

	switch (event) {
	case INIT:
		modelEc = initModel(((const InitArgs *) arg)->filename, model);
		drawingFunc = ((const InitArgs *) arg)->lineFunc;
		cleaningFunc = ((const InitArgs *) arg)->cleaningFunc;
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

	return modelEc;
}
