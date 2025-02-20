#include "Model.h"

#include <cstdlib>
#include <cstdio>

inline static
void
initStructure(Structure& modelStruct)
{
	modelStruct.edgeCount = 0;
	modelStruct.edges = nullptr;
	modelStruct.pointCount = 0;
	modelStruct.points = nullptr;
}

inline static
bool
structureIsEmpty(const Structure& model)
{
	return model.points == nullptr && model.edges == nullptr;
}

inline static
ModelEC
edgeFill_(FILE *file, Edge& edge)
{
	if (!file)
		return MODEL_ARG_ERROR;

	ModelEC ec = MODEL_OK;
	if (fscanf(file, "%d%d", &edge.from, &edge.to) != 2)
		ec = MODEL_FILE_ERROR;
	return ec;
}

static
ModelEC
createStructureFields_(Structure& modelStruct)
{
	ModelEC ec = MODEL_OK;
	if (modelStruct.edgeCount < 1 || modelStruct.pointCount < 1)
		ec = MODEL_FILE_ERROR;

	if (ec == MODEL_OK)
	{
		modelStruct.points = (Point *)calloc(modelStruct.pointCount, sizeof(Point));
		modelStruct.edges = (Edge *)calloc(modelStruct.edgeCount, sizeof(Edge));
	}

	if (ec == MODEL_OK && (!modelStruct.edges || !modelStruct.points))
	{
		ec = MODEL_MEMORY_ERROR;

		free(modelStruct.points);
		modelStruct.points = nullptr;

		free(modelStruct.edges);
		modelStruct.edges = nullptr;
	}

	return ec;
}

static
ModelEC
fillStructureFields_(const Structure& modelStruct, FILE *file)
{
	if (!file)
		return MODEL_FILE_ERROR;
	if (modelStruct.points == nullptr || modelStruct.edges == nullptr)
		return MODEL_ARG_ERROR;

	ModelEC ec = MODEL_OK;

	for (PointIdx i = 0; i < modelStruct.pointCount && ec == MODEL_OK; i++)
	{
		if (pointFill(file, modelStruct.points[i]) != POINT_OK)
			ec = MODEL_FILE_ERROR;
	}

	for (int i = 0; i < modelStruct.edgeCount && ec == MODEL_OK; i++)
		ec = edgeFill_(file, modelStruct.edges[i]);

	return ec;
}

static
void
relatePoints_(Point *points, const PointIdx pointCount, const Point& geometricCenter)
{
	if (!points)
		return;

	for (PointIdx i = 0; i < pointCount; i++)
		pointSub(points[i], geometricCenter);
}

static
ModelEC
initModelFilePtr_(FILE *file, Model& model)
{
	if (!file)
		return MODEL_FILE_ERROR;

	ModelEC ec = MODEL_OK;

	if (fscanf(file, "%d%d", &model.structure.pointCount, &model.structure.edgeCount) != 2)
		ec = MODEL_FILE_ERROR;

	if (ec == MODEL_OK)
		ec = createStructureFields_(model.structure);

	if (ec == MODEL_OK)
		ec = fillStructureFields_(model.structure, file);

	if (ec == MODEL_OK)
	{
		Point geometricCenter;
		pointsAverage(model.structure.points, model.structure.pointCount, geometricCenter);
		relatePoints_(model.structure.points, model.structure.pointCount, geometricCenter);

		model.position = geometricCenter;

		set3Scalars(model.rotation, 0, 0, 0);
		set3Scalars(model.scale, 1, 1, 1);
	}

	return ec;
}

ModelEC
initModel(const char *filename, Model& model)
{
	FILE *file = fopen(filename, "r");

	ModelEC ec = initModelFilePtr_(file, model);

	if (ec != MODEL_OK)
		modelFree(model);

	if (file)
		fclose(file);

	return ec;
}

ModelEC
modelFree(Model& model)
{
	if (!model.structure.points || !model.structure.edges)
		return MODEL_ARG_ERROR;

	free(model.structure.points);
	model.structure.points = nullptr;

	free(model.structure.edges);
	model.structure.edges = nullptr;
	return MODEL_OK;
}

void
modelSetPos(Model& model, const BASE3d& newPos)
{
	model.position = newPos;
}

void
modelSetRot(Model& model, const BASE3d& newRot)
{
	model.rotation = newRot;
}

void
modelSetScale(Model& model, const BASE3d& newScale)
{
	model.scale = newScale;
}

ModelEC
modelDraw(const Model& model, QGraphicsScene& scene)
{
	if (model.structure.points == nullptr || model.structure.edges == nullptr)
		return MODEL_ARG_ERROR;

	/* todo: check modelApplyTransformations
	 *	copy to point buffer
	 *	apply 3 transformations to each point
	 *	iterate through edges, for drawing lines
	*/
	ModelEC ec = MODEL_OK;

	auto *transformedPoints = (Point *)malloc(model.structure.pointCount * sizeof(Point));
	if (!transformedPoints)
		ec = MODEL_MEMORY_ERROR;
	else
		memmove(transformedPoints, model.structure.points, model.structure.pointCount * sizeof(Point));

	if (ec == MODEL_OK)
	{
		for (PointIdx i = 0; i < model.structure.pointCount; i++)
		{
			pointApplyScale(model.structure.points[i], model.scale);
			pointApplyRotation(model.structure.points[i], model.rotation);
			pointApplyReposition(model.structure.points[i], model.position);
		}

		for (int i = 0; i < model.structure.edgeCount; i++)
			scene.addLine(
					transformedPoints[model.structure.edges[i].from].x,
					transformedPoints[model.structure.edges[i].from].y,
					transformedPoints[model.structure.edges[i].to].x,
					transformedPoints[model.structure.edges[i].to].y
			);
	}

	free(transformedPoints);
	return ec;
}
