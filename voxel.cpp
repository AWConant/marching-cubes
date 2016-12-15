#include "voxel.h"

#include <iostream>

using namespace terr;

Voxel::Voxel(vec3 corner, vec3 *triangles, vec3 *normals, int numTriangles):
    m_color(0.0,0,1,1), m_firstDraw(true), m_vao(NULL), m_vbo(NULL), 
    m_corner(corner), m_triangles(triangles), m_normals(normals),
    m_numTriangles(numTriangles)
{
    m_dataSize = m_numTriangles * 3 * sizeof(vec3);

    if(initVBO()){
        m_vbo->bind();
        m_vbo->allocate(2*m_dataSize);
        m_vbo->write(0, m_triangles, m_dataSize);
        m_vbo->write(m_dataSize, m_normals, 2*m_dataSize);
        m_vbo->release();
    }
}

bool Voxel::initVBO(){
    m_vao = new QOpenGLVertexArrayObject();
    bool ok = m_vao->create();
    if( !ok ){ return false; }
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ok = m_vbo->create();
    if( !ok ){ return false; }
    m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    return ok;
}

Voxel::~Voxel(){
    if(m_vbo){
        m_vbo->release();
        delete m_vbo; m_vbo=NULL;
    }
    if(m_vao){
        m_vao->release();
        delete m_vao; m_vao=NULL;
    }
    delete m_triangles; m_triangles=NULL;
    delete m_normals; m_normals=NULL;
}

void Voxel::setupVAO(QOpenGLShaderProgram *prog) {
  m_vao->bind();
  m_vbo->bind();

  prog->setUniformValue("vColor", m_color);
  prog->enableAttributeArray("vPosition");
  prog->setAttributeBuffer("vPosition", GL_FLOAT, 0, 3, 0);

  prog->enableAttributeArray("vNormal");
  prog->setAttributeBuffer("vNormal", GL_FLOAT,
                           15 * (sizeof(vec3) + sizeof(vec2)), 3, 0);

  prog->enableAttributeArray("vTexture");
  //int texOffset = (m_stacks-2)*m_stripsize+2*(m_slices+2);
  //prog->setAttributeBuffer("vTexture",GL_FLOAT,texOffset*sizeof(vec3),2,0);

  m_vao->release();
  m_vbo->release();
}

void Voxel::draw(QOpenGLShaderProgram* prog){
    if (!prog) return;

    if (m_firstDraw) {
      setupVAO(prog);
      m_firstDraw = false;
    }

    m_vao->bind();
    prog->bind();

    prog->setUniformValue("vColor", m_color);
    prog->setUniformValue("vSColor", m_spec_color);
    //prog->enableAttributeArray("vTexture");
    //int texOffset = (m_stacks-2)*m_stripsize+2*(m_slices+2);
    //prog->setAttributeBuffer("vTexture",GL_FLOAT,texOffset*sizeof(vec3),2,0);

    glDrawArrays(GL_TRIANGLES, 0, m_numTriangles*3);

    prog->release();
    m_vbo->release();
    m_vao->release();
}
