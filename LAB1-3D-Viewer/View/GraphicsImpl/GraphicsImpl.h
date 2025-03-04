#ifndef LAB1_3D_VIEWER_GRAPHICSIMPL_H
#define LAB1_3D_VIEWER_GRAPHICSIMPL_H

#include "Model.h"
#include "DrawInterface.h"

void showError(ModelEC modelEc);
void lineDrawer(Point p1, Point p2, void *args);
void cleaningFunction(void *args);

#endif //LAB1_3D_VIEWER_GRAPHICSIMPL_H
