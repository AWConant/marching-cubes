#pragma once

#include <QtOpenGL>
#include <cmath>
#include <string>
#include "voxel.h"

//namespace terr {
    typedef QVector3D vec3;
    typedef QVector4D vec4;

    float density(vec3 p, std::string densityFunction);
    vec3 lerp(vec3 p1, vec3 p2, float d1, float d2);
    terr::Voxel *marchCube(float ***densities, vec3 ***gradients, vec3 corner, float stepSize);
    terr::Voxel **marchAll(vec3 fieldCorner, float fieldSize, int res,
                           std::string densityFunction);

//} // namespace
