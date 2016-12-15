#pragma once

#include <QtWidgets>
#include <QtOpenGL>
#include <QMatrix4x4>
#include "matrixstack.h"
#include "camera.h"
#include "voxel.h"


class MyPanelOpenGL : public QOpenGLWidget {
    Q_OBJECT

    typedef QVector4D point4;
    typedef QVector4D color4;
    typedef QVector3D vec3;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent* event);

public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    virtual ~MyPanelOpenGL();

private:
    /* Array of pointers to voxels dividing up the data field */
    terr::Voxel **m_voxels;

    int m_res;

    /* perspective projection angle */
    double m_angle;

    /* angle by which roll, pitch, yaw rotate */
    double m_rot_amt;

    /* distance by which up, down, left, right, forward, back move */
    double m_move_amt;

    QMatrix4x4 m_model; /* takes objects coordinates into world coordinates */
    QMatrix4x4 m_projection; /* takes world coordinates into clip coordinates */
    cs40::MatrixStack m_modelStack; /* history of past model matrices */
    cs40::Camera m_camera;

    /* shaders and program */
    QOpenGLShader *m_vertexShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShaderProgram *m_shaderProgram;

    /* print message showing keyboard controls */
    void showOptions();

    void createShaders();
    void destroyShaders();

signals:

public slots:
};
