#pragma once

#include <QtOpenGL>
#include <vector>

namespace terr {
    typedef QVector2D vec2;
    typedef QVector3D vec3;
    typedef QVector4D vec4;

class Voxel {

public:
    Voxel(vec3 corner, vec3 *triangles, vec3 *normals, int numTriangles);
    ~Voxel();

    void draw(QOpenGLShaderProgram *prog);

    inline void setColor(const vec3& color){ m_color=color; m_color.setW(1.); }
    inline vec4 getColor() const { return m_color; }

private:
    bool initVBO();
    void setupVAO(QOpenGLShaderProgram *prog);

protected:
    vec4 m_color;
    vec4 m_spec_color;
    bool m_firstDraw;

    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;

    vec3 m_corner;
    vec3 *m_triangles;
    vec3 *m_normals;

    int m_numTriangles;
    int m_dataSize;
};

} //namespace
