#include "GraphicsImpl.h"
#include "QMessageBox"
#include "QGraphicsScene"


void
showError(const ModelEC modelEc)
{
	const char *msg = nullptr;
	switch (modelEc)
	{
	case MODEL_FILE_ERROR:
		msg = "File error, figure can't be shown";
		break;
	case MODEL_UNKNOWN_ERROR:
		msg = "Unknown error";
		break;
	case MODEL_MEMORY_ERROR:
		msg = "Memory error, figure can't be shown";
		break;
	case MODEL_ARG_ERROR:
		msg = "Arg error, figure can't be shown";
		break;
	default:
		break;
	}
	if (msg)
		QMessageBox::critical(nullptr, "Error", msg);
}

void lineDrawer(Point p1, Point p2, void *args)
{
	if (!args)
		return;

	((QGraphicsScene *) args)->addLine(p1.x, p1.y, p2.x, p2.y);
}

void cleaningFunction(void *args)
{
	if (!args)
		return;

	((QGraphicsScene *) args)->clear();
}