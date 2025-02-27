#include "QMessageBox"

#include "ModelHandler.h"

static
void
showError(const ModelEC modelEc)
{
	switch (modelEc)
	{
	case MODEL_FILE_ERROR:
		QMessageBox::critical(nullptr, "Error", "File error, figure can't be shown");
		break;
	case MODEL_UNKNOWN_ERROR:
		QMessageBox::critical(nullptr, "Error", "Unknown error");
		break;
	case MODEL_MEMORY_ERROR:
		QMessageBox::critical(nullptr, "Error", "Memory error, figure can't be shown");
		break;
	case MODEL_ARG_ERROR:
		QMessageBox::critical(nullptr, "Error", "Arg error, figure can't be shown");
		break;
	default:
		break;
	}
}

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

	ModelEC ec = modelDraw(model, drawingFunc);
	return ec;
}


void
process(const Event event, const void *arg)
{
	static Model model;
	static LineDrawingFunc drawingFunc;
	static CleaningFunc cleaningFunc;

	ModelEC modelEc = MODEL_OK;

	switch (event)
	{
	case INIT:
		modelEc = initModel(((const InitArgs *)arg)->filename, model);
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

	showError(modelEc);
}
