#include "ModelHandler.h"

void
handle(
		const Event event,
		const Request &req,
		const CanvasTools canvasTools,
		const ErrorHandlerFunc showError
)
{
	static Model model;

	ModelEC modelEc = MODEL_OK;

	switch (event)
	{
		case INIT:modelEc = initModel(model, req.filename);
			break;
		case REPOS:modelSetPos(model, req.transform);
			break;
		case ROTATE:modelSetRot(model, req.transform);
			break;
		case SCALE:modelSetScale(model, req.transform);
			break;
		case EXIT:modelFree(model);
			break;
	}

	if (event != EXIT && modelEc == MODEL_OK)
		modelEc = screenUpdate(model, canvasTools);

	if (showError)
		showError(modelEc);
}
