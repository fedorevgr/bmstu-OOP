#include "ModelHandler.h"

void
handle(const Request& req)
{
	static Model model;

	ModelEC modelEc = MODEL_OK;

	switch (req.event)
	{
	case INIT:
		modelEc = initModel(model, req.filename);
		break;
	case REPOS:
		modelSetPos(model, req.transform);
		break;
	case ROTATE:
		modelSetRot(model, req.transform);
		break;
	case SCALE:
		modelSetScale(model, req.transform);
		break;
	case EXIT:
		modelFree(model);
		break;
	}

	if (req.event != EXIT && modelEc == MODEL_OK)
		modelEc = screenUpdate(model, req.drawTools);

	if (req.errorHandler)
		req.errorHandler(modelEc);
}

Request
composeRequest(
		const Event event,
		const char *filename,
		const BASE3d& transform,
		const ScreenTools& screenTools,
		const ErrorHandlerFunc errorHandler
)
{
	Request request;
	request.event = event;
	request.filename = filename;
	request.transform = transform;
	request.drawTools = screenTools;
	request.errorHandler = errorHandler;
	return request;
}
