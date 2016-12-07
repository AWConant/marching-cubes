#pragma once

#include <QMatrix4x4>
#include <QVector3D>

namespace cs40{

class MatrixStack
{
    typedef QVector3D vec3;

public:
    /* construct a stack containing identity matrix */
    MatrixStack();

    /* Return a modifiable reference to top of stack */
    QMatrix4x4& top();

    /* push copy of top onto stack */
    void push();

    /* pop top element off stack */
    void pop();

    /* translate matrix at top of stack in place
     * all matrix tranforms multiply on the right
     * of top */
    void translate(float dx, float dy, float dz);

    /* rotate matrix at top of stack CCW by angle (in degrees) around vec */
    void rotate(float angle, vec3 vec);

    inline void rotateX(float angle){ rotate(angle, vec3(1.,0.,0.)); }
    inline void rotateY(float angle){ rotate(angle, vec3(0.,1.,0.)); }
    inline void rotateZ(float angle){ rotate(angle, vec3(0.,0.,1.)); }

    /* scales matrix at top of stack in place */
    void scale(float fac);

private:
    QList<QMatrix4x4> m_stack;
};

} // namespace

