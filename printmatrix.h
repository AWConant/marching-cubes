#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <ostream>

// In case you want to cout a QMatrix4x4
std::ostream& operator<<(std::ostream& str, const QMatrix4x4& mat);
