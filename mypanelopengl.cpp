#include "mypanelopengl.h"
#include "marching.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) : QOpenGLWidget(parent) {
    m_shaderProgram=NULL;
    m_vertexShader=NULL;
    m_fragmentShader=NULL;

    m_move_amt = 15;
    m_rot_amt = 10;
    m_angle = 45;

    m_gradientNormals = true;

    /* Put the camera in a reasonable initial position */
    m_camera.back(250);
    m_camera.up(70);
    m_camera.right(80);
      
    m_modelStack.push();
    
    showOptions();

    /* Get command line arguments from high-level QT application */
    QStringList args = QCoreApplication::arguments();
    m_densityFunction = args.at(1).toStdString();
    m_res = args.at(2).toFloat();
    m_fieldSize = args.at(3).toFloat();
    m_gradientNormals = args.at(4).toFloat();
}

MyPanelOpenGL::~MyPanelOpenGL() {
    m_shaderProgram->release();
    destroyShaders();
    for (int i = 0; i < m_res*m_res*m_res; i++) delete m_voxels[i];
    delete [] m_voxels;
}

void MyPanelOpenGL::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
    createShaders();

    /* Initialize perspective projection */
    m_projection.perspective(m_angle, 1, 0.1, -0.1);

    m_shaderProgram->bind();

    /* Create triangle geometry for all voxels based on density function */
    m_voxels = marchAll(vec3(), m_fieldSize, m_res, m_densityFunction,
                        m_gradientNormals);

}

void MyPanelOpenGL::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void MyPanelOpenGL::paintGL() {
    /* clear both color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!m_shaderProgram) { return; }

    m_shaderProgram->bind();
    QMatrix4x4 mview = m_camera.matrix() * m_model;
    m_shaderProgram->setUniformValue("Tex0",0);
    m_shaderProgram->setUniformValue("model", m_model);
    m_shaderProgram->setUniformValue("projection", m_projection);
    m_shaderProgram->setUniformValue("camera", m_camera.matrix());
    m_shaderProgram->setUniformValue("modelView", mview);
    m_shaderProgram->setUniformValue("normalMatrix", mview.normalMatrix());
    m_shaderProgram->setUniformValue("lightPos", vec4(60, 100, 60, 1.));

    /* Draw the geometry inside every Voxel */
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
