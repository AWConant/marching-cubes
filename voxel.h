#pragma once

#include <QtOpenGL>

namespace terr {
    typedef QVector3D vec3;
    typedef QVector4D vec4;

class Voxel {
public:
    Voxel(vec3 corner, vec3 *triangles, int numTriangles);
    ~Voxel();

    void draw(QOpenGLShaderProgram *prog);

    inline void setColor(const vec3& color){ m_color=color; m_color.setW(1.); }
    inline vec4 getColor() const { return m_color; }

private:
    bool initVBO();

protected:
    vec4 m_color;
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    vec3 *m_triangles;
    vec3 m_corner;
    int m_numTriangles;
};

} //namespace
