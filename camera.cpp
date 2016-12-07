#include "camera.h"

using namespace cs40;


Camera::Camera() {
  reset();
}

/* Reproduce behavior of QMatrix4x4::lookAt, return new matrix */
mat4 Camera::lookAt(const vec3& eye, const vec3& at, const vec3& up) {
    vec3 eye2at_normal = (at - eye).normalized();
    vec3 up_normal = up.normalized();

    vec3 lookat_row0 = vec3::crossProduct(eye2at_normal, up_normal);
    vec3 lookat_row1 = vec3::crossProduct(lookat_row0, eye2at_normal);
    
    mat4 lookat;
    lookat.setRow(0, vec4(lookat_row0, 0));
    lookat.setRow(1, vec4(lookat_row1, 0));
    lookat.setRow(2, vec4(-eye2at_normal, 0));
    
    mat4 translate_eye;
    translate_eye.setColumn(3, vec4(-eye, 1));

    return lookat * translate_eye;
}

/* move camera right by amount amt. Scene should shift left
 *    amt is in world units */
void Camera::right(float amt) {
    mat4 translate_by; translate_by.translate(-amt, 0, 0);
    m_lookAt = translate_by * m_lookAt;
}
void Camera::up(float amt) {
    mat4 translate_by; translate_by.translate(0, -amt, 0);
    m_lookAt = translate_by * m_lookAt;
}
void Camera::forward(float amt) {
    mat4 translate_by; translate_by.translate(0, 0, amt);
    m_lookAt = translate_by * m_lookAt;
}

/* rotate CCW about -z axis _of camera_
 *    angle is in degrees */
void Camera::roll(float angle) {
    mat4 rotate_by; rotate_by.rotate(angle, 0, 0, 1);
    m_lookAt = rotate_by * m_lookAt;
}
void Camera::pitch(float angle) {
    mat4 rotate_by; rotate_by.rotate(angle, 1, 0, 0);
    m_lookAt = rotate_by * m_lookAt;
}
void Camera::yaw(float angle) {
    mat4 rotate_by; rotate_by.rotate(angle, 0, 1, 0);
    m_lookAt = rotate_by * m_lookAt;
}

/* reset camera to default location as in constructor */
void Camera::reset() {
  vec3 default_eye(0, 0, 5);
  vec3 default_at(0, 0, 0);
  vec3 default_up(0, 1, 0);

  m_lookAt = lookAt(default_eye, default_at, default_up);
}
