#include "ModelHandler.h"

void fillInitArgs(
		InitArgs& argStruct,
		const char *fName, LineDrawingFunc func, CleaningFunc clean)
{
	argStruct.lineFunc = func;
	argStruct.filename = fName;
	argStruct.cleaningFunc = clean;
}

static inline
ModelEC
screenUpdate(const Model& model, const CleaningFunc cleaningFunc, const LineDrawingFunc drawingFunc)
{
	if (cleaningFunc == nullptr)
		return MODEL_ARG_ERROR;

	cleaningFunc(nullptr);

	return modelDraw(model, drawingFunc);
}


void
modelHandle(const Event event, const void *arg, const ErrorHandlerFunc showError)
{
	static Model model;
	static LineDrawingFunc drawingFunc;
	static CleaningFunc cleaningFunc;

	ModelEC modelEc = MODEL_OK;

	switch (event)
	{
	case INIT:
		modelEc = initModel(model, ((const InitArgs *)arg)->filename);
		cleaningFunc = ((const InitArgs *)arg)->cleaningFunc;
		drawingFunc = ((const InitArgs *)arg)->lineFunc;
		break;
	case REPOS:modelSetPos(model, *(BASE3d *)arg);
		break;
	case ROTATE:modelSetRot(model, *(BASE3d *)arg);
		break;
	case SCALE:modelSetScale(model, *(BASE3d *)arg);
		break;
	case EXIT:modelFree(model);
		break;
	}

	if (event != EXIT && modelEc == MODEL_OK)
		modelEc = screenUpdate(model, cleaningFunc, drawingFunc);

	if (showError)
		showError(modelEc);
}
