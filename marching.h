#pragma once

#include <QtOpenGL>
#include <cmath>
#include <string>

#include "voxel.h"

typedef QVector3D vec3;
typedef QVector4D vec4;

float density(vec3 p, std::string densityFunction);

/* Return point between p1 and p2, linearly interpolated based on d1 and
    * d2, the density values at p1 and p2. */
vec3 lerp(vec3 p1, vec3 p2, float d1, float d2);

terr::Voxel *marchCube(float ***densities, vec3 ***gradients,
                        vec3 corner, float stepSize, float gradNorms);

terr::Voxel **marchAll(vec3 fieldCorner, float fieldSize, int res,
                        std::string densityFunction, float gradNorms);
