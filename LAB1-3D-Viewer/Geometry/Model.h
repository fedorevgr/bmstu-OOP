#ifndef MODEL_H
#define MODEL_H

#include "Point.h"

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

typedef _3DBASE_ Rotation;
typedef _3DBASE_ Scale;

typedef struct Model_ {
    Structure structure;
    Point position;
    Rotation rotation;
    Scale scale;
} Model;

typedef enum ModelEC_ {
    MODEL_OK,
    MODEL_MEMORY_ERROR,
    MODEL_FILE_ERROR,
    MODEL_ARG_ERROR,
    MODEL_UNKNOWN_ERROR
} ModelEC;

ModelEC modelFromFile(const char *filename, Model **model);
void modelFree(Model *model);

#endif //MODEL_H
