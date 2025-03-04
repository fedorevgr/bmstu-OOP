#ifndef MODEL_H
#define MODEL_H

#include "Point.h"

typedef void (*LineDrawingFunc)(BASE3d, BASE3d, void *);

typedef int PointIdx;

typedef struct Edge_ {
    PointIdx from, to;
} Edge;

typedef struct Structure_ {
    Point *points;
    PointIdx pointCount;

    Edge *edges;
    int edgeCount;
} Structure;

typedef struct Model_ {
    Structure structure;
    BASE3d position;
    BASE3d rotation;
    BASE3d scale;
} Model;

typedef enum ModelEC_ {
    MODEL_OK,
    MODEL_MEMORY_ERROR,
    MODEL_FILE_ERROR,
    MODEL_ARG_ERROR,
    MODEL_UNKNOWN_ERROR
} ModelEC;

ModelEC initModel(Model &model, const char* filename);
void modelFree(Model &model);

void modelSetPos(Model &model, const BASE3d &newPos);
void modelSetRot(Model &model, const BASE3d &newRot);
void modelSetScale(Model &model, const BASE3d &newScale);

ModelEC modelDraw(const Model& model, LineDrawingFunc lineDrawer);


#endif //MODEL_H
