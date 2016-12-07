#include "mypanelopengl.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using cs40::Sphere;
using cs40::Square;
using cs40::Planet;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QOpenGLWidget(parent), m_angles(0,0.,0.) {

    m_shaderProgram=NULL;
    m_vertexShader=NULL;
    m_fragmentShader=NULL;

    m_sphere = NULL;

    m_timer = NULL;

    m_rot_speed = 1000;
    m_move_amt = 0.4;
    m_rot_amt = 6;
    m_angle = 45;
    m_quake_mag = 0.2;

    /* rotate to fix the axes */
    m_modelStack.push();
    m_modelStack.rotateX(-90);

    srand(time(NULL));

    m_polymode = 2;

    showOptions();
}

MyPanelOpenGL::~MyPanelOpenGL() {
    m_shaderProgram->release();

    delete m_sphere;

    delete m_timer;
    for (int i = 0; i < m_planets.length(); i++) {
        delete m_planets[i];
    }

    destroyShaders();
}

void MyPanelOpenGL::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    createShaders();

    createPlanetsFromInput("solarData.txt");

    m_sphere = new Sphere(5,30,30);

    m_projection.perspective(m_angle, 1, 0.1, -0.1);

    m_shaderProgram->bind();

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    m_timer->start(10);
}

void MyPanelOpenGL::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void MyPanelOpenGL::paintGL() {
    /* clear both color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updatePolyMode(m_polymode);
    glEnable(GL_CULL_FACE);

    if (!m_shaderProgram) { return; }
    
    double vertical;
    double horizontal;
    double quake_disp;
    if (m_quake) {
        quake_disp = m_quake_mag * sin(0.15 * m_quake_time * M_PI/180);
        vertical = 2*quake_disp*(double(rand())/RAND_MAX) - quake_disp;
        horizontal = 2*quake_disp*(double(rand())/RAND_MAX) - quake_disp;
        m_camera.up(vertical);
        m_camera.right(horizontal);
        m_quake_time += 1;
    }

    m_shaderProgram->bind();
    m_shaderProgram->setUniformValue("Tex0",0);
    m_shaderProgram->setUniformValue("model", m_model);
    m_shaderProgram->setUniformValue("projection", m_projection);
    m_shaderProgram->setUniformValue("camera", m_camera.matrix());

    if (m_quake) {
        m_camera.down(vertical);
        m_camera.left(horizontal);
    }

    /* Draw each of the planets */
    for (int i = 0; i < m_planets.length(); i++) {
        drawPlanet(m_planets[i], false);
    }

    glFlush();
}

void MyPanelOpenGL::drawPlanet(cs40::Planet* planet, bool isMoon) {
    m_modelStack.push();

    /* rotate according to inclination w/ respect to disk defined by sun's
      * X and Y axes */
    m_modelStack.rotateY(planet->getInclination());

    /* rotate according to time of year */
    m_modelStack.rotateZ(planet->getOrbPos());

    /* For planets, move in a bit to accommodate for orbit radius stretching
     * from log transformation for inner planets */
    double orbitDist = 0;
    if (planet->getOrbitRadius()) {
      orbitDist = log2(planet->getOrbitRadius());
      if (!isMoon) {
          orbitDist -= log2(m_planets[1]->getOrbitRadius() / 3);
      }
    }

    /* translate to distance from center of orbit */
    m_modelStack.translate(orbitDist, 0, 0);

    /* rotate according to tilt w/ respect to sun's Z axis */
    m_modelStack.rotateZ(-planet->getOrbPos());
    m_modelStack.rotateY(planet->getTilt());
    m_modelStack.rotateZ(planet->getOrbPos());

    /* Draw planet's moons */
    for (int i = 0; i < planet->getMoons()->length(); i++) {
        drawPlanet(planet->getMoons()->at(i), true);
    }

    /* rotate according to time of day */
    m_modelStack.rotateZ(planet->getRotPos());

    /* scale to correct planetary radius */
    m_modelStack.scale(log10(planet->getRadius()) / 25);

    m_shaderProgram->setUniformValue("model", m_modelStack.top());
    planet->getTexture()->bind();

    m_sphere->draw(m_shaderProgram);
    m_modelStack.pop();
}

void MyPanelOpenGL::showOptions() {
  printf("\nApplication controls: \n");
  printf("-: Slow down time\n");
  printf("=: Speed up time\n");
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
  printf("Space: Toggle spacequake\n\n");
}

void MyPanelOpenGL::keyPressEvent(QKeyEvent *event) {
    /*Enable strong Focus on GL Widget to process key events*/
    switch(event->key()){
    case Qt::Key_Minus:
        m_rot_speed /= 1.5;
        break;
    case Qt::Key_Equal:
        m_rot_speed *= 1.5;
        break;
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
    case Qt::Key_Space:
        m_quake = !m_quake;
        m_quake_time = 0;
        break;
    default:
        QWidget::keyPressEvent(event); /* pass to base class */
    }
    cs40::mat4 new_proj; new_proj.perspective(m_angle, 1, 0.1, -0.1);
    m_projection = new_proj;
    update();
}

void MyPanelOpenGL::createPlanetsFromInput(const QString &fname) {
    std::ifstream infile;
    std::string name;
    QString qname;
    char buf[1024];
    float rad, o_rad, o_tau, ecc, inc, r_tau, tilt;
    int moons;
    Planet* planet = NULL;
    Planet* currPlanet = NULL;
    
    infile.open(fname.toStdString().c_str());

    /* read header lines */
    infile.getline(buf,1024);
    infile.getline(buf,1024);
    name = "";

    int currPlanetMoons = 0;
    while(!infile.eof()){
        infile >> name >> rad >> o_rad >> o_tau >> ecc >> inc >> r_tau >> tilt
               >> moons;
        if(!infile.eof()){
            qname = QString(name.c_str()).toLower();
            /* construct planet with fields and texture */
            planet = new Planet(qname, o_rad, o_tau, ecc, inc, rad, r_tau, 
                                tilt);

            /* If 'planet' is a moon, add it to current planet as a moon, using
             * the default moon texture */
            if (currPlanetMoons) {
                planet->setTexture("data/moon.png");
                currPlanet->addMoon(planet);
                currPlanetMoons--;
            }
            /* If 'planet' is actually a planet, just add it to m_planets */
            else {
                planet->setTexture("data/" + qname + ".png");
                m_planets.append(planet);
                currPlanet = planet;
                currPlanetMoons = moons;
            }
        }
    }
}

void MyPanelOpenGL::updateTime() {
    for (int i = 0; i < m_planets.length(); i++) {
        m_planets[i]->move(m_rot_speed/100);
    }
    /* trigger a refresh */
    update();
}

void MyPanelOpenGL::updatePolyMode(int val) {
    GLenum mode=GL_NONE;
    if(val==0){mode=GL_POINT;}
    else if(val==1){mode=GL_LINE;}
    else if(val==2){mode=GL_FILL;}

    if(mode != GL_NONE){
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}

void MyPanelOpenGL::createShaders() {

    destroyShaders(); //get rid of any old shaders

    m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    if (!m_vertexShader->compileSourceFile("shaders/vshader.glsl")){
        qWarning() << m_vertexShader->log();
    }

    m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    if(!m_fragmentShader->compileSourceFile("shaders/fshader.glsl")){
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

void MyPanelOpenGL::updateAngles(int idx, qreal amt) {
    if(idx == 0){
        m_angles.setX(m_angles.x()+amt);
    }else if(idx == 1){
        m_angles.setY(m_angles.y()+amt);
    }else if(idx == 2){
        m_angles.setZ(m_angles.z()+amt);
    }
}


qreal MyPanelOpenGL::wrap(qreal amt) {
    if (amt > 360.){ return amt - 360.; }
    else if (amt < 0.){ return amt + 360.; }
    return amt;
}
