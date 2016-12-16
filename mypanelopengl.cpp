#include "mypanelopengl.h"
#include "marching.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
//using terr::marchAll;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) : QOpenGLWidget(parent) {
    m_shaderProgram=NULL;
    m_vertexShader=NULL;
    m_fragmentShader=NULL;

    m_move_amt = 0.4;
    m_rot_amt = 6;
    m_angle = 45;

    // m_camera.pitch(-15 * m_rot_amt);
    // m_camera.yaw(6 * m_rot_amt);
    m_camera.back(80*m_move_amt);
    m_camera.up(40*m_move_amt);
    m_camera.right(80*m_move_amt);
      
    /* rotate to fix the axes */
    m_modelStack.push();
    // m_modelStack.rotateX(-90);
    
    //showOptions();
}

MyPanelOpenGL::~MyPanelOpenGL() {
    m_shaderProgram->release();
    destroyShaders();
}

void MyPanelOpenGL::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
    createShaders();

    m_projection.perspective(m_angle, 1, 0.1, -0.1);

    m_shaderProgram->bind();

    m_fieldCorner = vec3();
    m_res = 30;
    m_fieldSize = 60;

    m_voxels = marchAll(m_fieldCorner, m_fieldSize, m_res);

    //glEnable(GL_LIGHTING);
}

void MyPanelOpenGL::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void MyPanelOpenGL::paintGL() {
    /* clear both color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glEnable(GL_CULL_FACE);

    if (!m_shaderProgram) { return; }

    m_shaderProgram->bind();
    QMatrix4x4 mview = m_camera.matrix() * m_model;
    m_shaderProgram->setUniformValue("Tex0",0);
    m_shaderProgram->setUniformValue("model", m_model);
    m_shaderProgram->setUniformValue("projection", m_projection);
    m_shaderProgram->setUniformValue("camera", m_camera.matrix());
    m_shaderProgram->setUniformValue("modelView", mview);
    m_shaderProgram->setUniformValue("normalMatrix", mview.normalMatrix());
    m_shaderProgram->setUniformValue("lightPos", vec4(10.0, 50.0, 0, 1.));

    for (int i = 0; i < m_res*m_res*m_res; i++) {
        m_voxels[i]->draw(m_shaderProgram);
    }

    glFlush();
}

void MyPanelOpenGL::showOptions() {
  printf("\nApplication controls: \n");
  printf("W: Zoom in\n");
  printf("S: Zoom out\n");
  printf("W+Shift: Pan up\n");
  printf("S+Shift: Pan down\n");
  printf("A: Pan left\n");
  printf("D: Pan right\n");
  printf("Up: Pitch up\n");
  printf("Down: Pitch up\n");
  printf("Left: Yaw left\n");
  printf("Right: Yaw right\n");
  printf("Left+Shift: Roll left\n");
  printf("Right+Shift: Roll right\n");
  printf("R: reset\n");
  printf("Q: Decrease perspective angle\n");
  printf("E: Increase perspective angle\n");
}

void MyPanelOpenGL::keyPressEvent(QKeyEvent *event) {
    /*Enable strong Focus on GL Widget to process key events*/
    switch(event->key()){
    case Qt::Key_W:
        if (event->modifiers() & Qt::ShiftModifier) { m_camera.up(m_move_amt); }
        else { m_camera.forward(m_move_amt); }
        break;
    case Qt::Key_A:
        m_camera.left(m_move_amt);
        break;
    case Qt::Key_S:
        if (event->modifiers() & Qt::ShiftModifier) { m_camera.down(m_move_amt); }
        else { m_camera.back(m_move_amt); }
        break;
    case Qt::Key_D:
        m_camera.right(m_move_amt);
        break;
    case Qt::Key_Up:
        m_camera.pitch(-m_rot_amt);
        break;
    case Qt::Key_Down:
        m_camera.pitch(m_rot_amt);
        break;
    case Qt::Key_Right:
        if (event->modifiers() & Qt::ShiftModifier) { m_camera.roll(m_rot_amt); }
        else { m_camera.yaw(m_rot_amt); }
        break;
    case Qt::Key_Left:
        if (event->modifiers() & Qt::ShiftModifier) { m_camera.roll(-m_rot_amt); }
        else { m_camera.yaw(-m_rot_amt); }
        break;
    case Qt::Key_R:
        m_camera.reset();
        break;
    case Qt::Key_Q:
        m_angle -= 5;
        break;
    case Qt::Key_E:
        m_angle += 5;
        break;
    default:
        QWidget::keyPressEvent(event); /* pass to base class */
    }
    cs40::mat4 new_proj; new_proj.perspective(m_angle, 1, 0.1, -0.1);
    m_projection = new_proj;
    update();
}

void MyPanelOpenGL::createShaders() {

    destroyShaders(); //get rid of any old shaders

    m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    if (!m_vertexShader->compileSourceFile("shaders/vfraglight.glsl")){
        qWarning() << m_vertexShader->log();
    }

    m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    if(!m_fragmentShader->compileSourceFile("shaders/ffraglight.glsl")){
        qWarning() << m_fragmentShader->log();
    }

    m_shaderProgram = new QOpenGLShaderProgram();
    m_shaderProgram->addShader(m_vertexShader);
    m_shaderProgram->addShader(m_fragmentShader);

    if(!m_shaderProgram->link()){
        qWarning() << m_shaderProgram->log() << endl;
    }
}

void MyPanelOpenGL::destroyShaders() {

    delete m_vertexShader; m_vertexShader=NULL;
    delete m_fragmentShader; m_fragmentShader=NULL;

    if(m_shaderProgram){
        m_shaderProgram->release();
        delete m_shaderProgram; m_shaderProgram=NULL;
    }
}
