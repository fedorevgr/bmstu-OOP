//
// Created by lpacw on 2/19/2025.
//

#ifndef LINEARSPACE_H
#define LINEARSPACE_H

typedef double SCALAR;

typedef struct
{
    SCALAR x, y, z;
} BASE3d;

void init3Scalars(BASE3d &, SCALAR, SCALAR, SCALAR);

#endif //LINEARSPACE_H
