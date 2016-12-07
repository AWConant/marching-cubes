#include "matrixstack.h"

using namespace cs40;

MatrixStack::MatrixStack()
{
    m_stack.append(QMatrix4x4());
}

QMatrix4x4& MatrixStack::top(){
    /* return identity if empty stack */
    if (m_stack.size() == 0){
        m_stack.append(QMatrix4x4());
    }
    return m_stack.back();
}

void MatrixStack::push(){
    m_stack.append(m_stack.back());
}

void MatrixStack::pop(){
    if(m_stack.size()>0){
        m_stack.pop_back();
    }
}

void MatrixStack::translate(float dx, float dy, float dz){
    top().translate(dx,dy,dz);
}

void MatrixStack::scale(float factor){
    top().scale(factor);
}

void MatrixStack::rotate(float angle, vec3 vec){
    top().rotate(angle,vec);
}
