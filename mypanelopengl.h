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

    /* Number of voxels per edge of containing cube */
    int m_res;

    /* Determines the side lengths of the large cubic region to be marched.
     * Will be divided into m_res Voxels each with side length
     * m_res/m_fieldSize */
    float m_fieldSize;

    /* Bottom back left corner of containing cube */
    vec3 m_fieldCorner;

    /* perspective projection angle */
    double m_angle;

    /* angle by which roll, pitch, yaw rotate */
    double m_rot_amt;

    /* distance by which up, down, left, right, forward, back move */
    double m_move_amt;

    /* 1 if using interpolated gradient normals, 0 if using triangle face
     * normals.  */
    float m_gradientNormals;

    QMatrix4x4 m_model; /* takes objects coordinates into world coordinates */
    QMatrix4x4 m_projection; /* takes world coordinates into clip coordinates */
    cs40::MatrixStack m_modelStack; /* history of past model matrices */
    cs40::Camera m_camera;

    /* shaders and program */
    QOpenGLShader *m_vertexShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShaderProgram *m_shaderProgram;

    /* Density function for marching cubes */
    std::string m_densityFunction;

    /* print message showing keyboard controls */
    void showOptions();

    void createShaders();
    void destroyShaders();

signals:

public slots:
};
