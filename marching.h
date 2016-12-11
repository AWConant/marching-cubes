#pragma once

#include "voxel.h"

#include <QtOpenGL>
#include <cmath>

namespace terr {
    typedef QVector3D vec3;
    typedef QVector4D vec4;

float sample(vec3 p);
Voxel *marchCube(vec3 corner, float stepSize);
Voxel **marchAll(vec3 fieldCorner, float fieldSize, int res);

} // namespace
