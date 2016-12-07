#pragma once

#include <QtWidgets>
#include <QtOpenGL>
#include <QMatrix4x4>
#include "sphere.h"
#include "square.h"
#include "matrixstack.h"
#include "camera.h"
#include "planet.h"


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
    cs40::Sphere* m_sphere;

    /* perspective projection angle */
    double m_angle;

    /* whether earthquake mode is engaged or not */
    bool m_quake;

    /* maximum magnitude of earthquake transformations*/
    double m_quake_mag;

    /* time in paintGL iterations since earthquake started*/
    double m_quake_time;

    /* hours by which solar system time is advanced each second of real time */
    double m_rot_speed;

    /* angle by which roll, pitch, yaw rotate */
    double m_rot_amt;

    /* distance by which up, down, left, right, forward, back move */
    double m_move_amt;

    /* Polygon draw mode
     * 0 : point
     * 1 : line
     * 2 : polygon */
    int m_polymode;

    QMatrix4x4 m_model; /* takes objects coordinates into world coordinates */
    QMatrix4x4 m_projection; /* takes world coordinates into clip coordinates */
    cs40::MatrixStack m_modelStack; /* history of past model matrices */
    cs40::Camera m_camera;

    QList<cs40::Planet*> m_planets;

    /* set this up when you are ready to animate */
    QTimer* m_timer;      /* event timer */

    vec3 m_angles; /* Euler angles for rotation */

    /* shaders and program */
    QOpenGLShader *m_vertexShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShaderProgram *m_shaderProgram;

    /* draw a planet */
    void drawPlanet(cs40::Planet* planet, bool isMoon);

    /* parse planet data into m_planets */
    void createPlanetsFromInput(const QString& fname);

    /* print message showing keyboard controls */
    void showOptions();

    /* update Polygon draw mode based
     * 0 : point
     * 1 : line
     * 2 : polygon */
    void updatePolyMode(int val);

    void createShaders();
    void destroyShaders();

    /* update Euler angle at index idx by amt
     * idx=0,1,2 -> x,y,z */
    void updateAngles(int idx, qreal amt);

    /* wrap a angle value to the range 0..360*/
    qreal wrap(qreal amt);

signals:

public slots:
    /* trigger update of GL window */
    void updateTime(); 
};
