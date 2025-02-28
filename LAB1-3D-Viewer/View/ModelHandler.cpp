#include "ModelHandler.h"

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
modelHandle(
		const Event event,
		const void *arg,
		const LineDrawingFunc drawingFunc,
		const CleaningFunc cleaningFunc,
		const ErrorHandlerFunc showError
)
{
	static Model model;

	ModelEC modelEc = MODEL_OK;

	switch (event)
	{
	case INIT:
		modelEc = initModel(model, ((const char *)arg));
		break;
	case REPOS:
		modelSetPos(model, *(BASE3d *)arg);
		break;
	case ROTATE:
		modelSetRot(model, *(BASE3d *)arg);
		break;
	case SCALE:
		modelSetScale(model, *(BASE3d *)arg);
		break;
	case EXIT:
		modelFree(model);
		break;
	}

	if (event != EXIT && modelEc == MODEL_OK)
		modelEc = screenUpdate(model, cleaningFunc, drawingFunc);

	if (showError)
		showError(modelEc);
}
