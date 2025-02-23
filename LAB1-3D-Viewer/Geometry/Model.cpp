#include "Model.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

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

		set3Scalars(model.position, 0, 0, 0);
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

void
modelFree(Model& model)
{
	if (model.structure.points) {
		free(model.structure.points);
		model.structure.points = nullptr;
	}
	if (model.structure.edges) {
		free(model.structure.edges);
		model.structure.edges = nullptr;
	}
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
modelDraw(const Model& model, LineDrawingFunc lineFunc)
{
	if (!model.structure.points || !model.structure.edges || !lineFunc)
		return MODEL_ARG_ERROR;

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
			pointApplyScale(transformedPoints[i], model.scale);
			pointApplyRotation(transformedPoints[i], model.rotation);
			pointApplyReposition(transformedPoints[i], model.position);
		}

		for (int i = 0; i < model.structure.edgeCount; i++)
			lineFunc(
					transformedPoints[model.structure.edges[i].from].x,
					transformedPoints[model.structure.edges[i].from].y,
					transformedPoints[model.structure.edges[i].to].x,
					transformedPoints[model.structure.edges[i].to].y,
					nullptr
			);
	}

	free(transformedPoints);
	return ec;
}

void
modelPrint(const Model &model)
{
	printf("Model\n");
	printf("\tPos\n\t\t%lf, %lf, %lf\n", model.position.x, model.position.y, model.position.z);
	printf("\tRot\n\t\t%lf, %lf, %lf\n", model.rotation.x, model.rotation.y, model.rotation.z);
	printf("\tScale\n\t\t%lf, %lf, %lf\n", model.scale.x, model.scale.y, model.scale.z);
	printf("\tStructure\n");

	if (!model.structure.points || !model.structure.edges)
		printf("\t\tUninitialized structure\n");
	else
	{
		for (PointIdx i = 0; i < model.structure.pointCount; i++)
			printf("\t\t%lf, %lf, %lf\n", model.structure.points[i].x, model.structure.points[i].y, model.structure.points[i].z);
	}
}
