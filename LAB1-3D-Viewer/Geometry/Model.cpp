#include "Model.h"

#include <cstdlib>
#include <cstdio>

static
ModelEC
createStructureFields_(Structure *modelStruct) {
    ModelEC ec = MODEL_OK;
    if (modelStruct->edgeCount < 1 || modelStruct->pointCount < 1)
        ec = MODEL_FILE_ERROR;

    if (ec == MODEL_OK) {
        modelStruct->points = (Point *) calloc(modelStruct->pointCount, sizeof(Point));
        modelStruct->edges = (Edge *) calloc(modelStruct->edgeCount, sizeof(Edge));
    }

    if (ec == MODEL_OK && (!modelStruct->edges || !modelStruct->points)) {
        ec = MODEL_MEMORY_ERROR;

        free(modelStruct->points);
        modelStruct->points = nullptr;

        free(modelStruct->edges);
        modelStruct->edges = nullptr;
    }

    return ec;
}

static
ModelEC
fillStructureFields_(const Structure *modelStruct, FILE *file) {
    ModelEC ec = MODEL_OK;

    for (PointIdx i = 0; i < modelStruct->pointCount && ec == MODEL_OK; i++) {
        if (pointFill(file, modelStruct->points + i) != POINT_OK)
            ec = MODEL_FILE_ERROR;
    }

    for (int  i = 0; i < modelStruct->edgeCount && ec == MODEL_OK; i++) {
        if (fscanf(file, "%d%d", &modelStruct->edges[i].from, &modelStruct->edges[i].to) != 2)
            ec = MODEL_FILE_ERROR;
    }

    return ec;
}


static
ModelEC
modelFromFilePtr_(FILE *f, Model **model) {
    if (!f || !model)
        return MODEL_ARG_ERROR;

    ModelEC ec = MODEL_OK;

    auto *tempModel = (Model *) malloc(sizeof(Model));
    if (!tempModel)
        ec = MODEL_MEMORY_ERROR;

    if (ec == MODEL_OK && fscanf(f, "%d%d", tempModel->structure.pointCount, tempModel->structure.edgeCount) != 2)
        ec = MODEL_FILE_ERROR;

    if (ec == MODEL_OK)
        ec = createStructureFields_(&tempModel->structure);

    if (ec  == MODEL_OK)
        ec = fillStructureFields_(&tempModel->structure, f);

    if  (ec == MODEL_OK) {
        pointsAverage(tempModel->structure.points, tempModel->structure.pointCount, &tempModel->position);
        tempModel->rotation = (Rotation) { 0, 0, 0 };
        tempModel->scale = (Scale) { 1, 1, 1 };
    }

    if (ec != MODEL_OK)
        modelFree(tempModel);
    return ec;
}


ModelEC
modelFromFile(const char *filename, Model **model) {
    ModelEC ec = MODEL_OK;
    FILE *f = fopen(filename, "r");
    if (!f)
        ec = MODEL_FILE_ERROR;

    if (ec == MODEL_OK)
        ec = modelFromFilePtr_(f, model);

    return ec;
}

void
modelFree(Model *model) {
    if  (!model)
        return;

    free(model->structure.points);
    free(model->structure.edges);
    free(model);
}
