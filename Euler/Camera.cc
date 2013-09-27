// Author: Matthew Wraith

#include "Camera.h"

// Set the position of the camera. I use this for initialization.
// pos is the position. view is where the camera is looking. up is
// the up direction.
void Camera::setCameraPosition(
        double px, double py, double pz,
        double vx, double vy, double vz,
        double ux, double uy, double uz) {
    pos = vec3(px, py, pz);
    view = vec3(vx, vy, vz);
    up = vec3(ux, vy, vz); // Define up.
}

// Draw the screen, and draw a crosshair
void Camera::drawCamera() {
    gluLookAt(
        pos.x,  pos.y,  pos.z,
        view.x, view.y, view.z,
        up.x,   up.y,   up.z
    );

    drawCross();
}

// Draw a crosshair
void Camera::drawCross() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
        glVertex3f(view.x, view.y, view.z);
    glEnd();
}

// Mouse calculations
void Camera::moveMouse() {
    int mouseX;
    int mouseY;
    int width = WINSIZEX;
    int height = WINSIZEY;
    int midX = width >> 1;
    int midY = height >> 1;
    double angle_y = 0.0;
    double angle_z = 0.0;

    SDL_GetMouseState(&mouseX, &mouseY);

    if((mouseX == midX) && (mouseY == midY)) return;

    SDL_WarpMouse(midX, midY);

    angle_y = (double)(midX - mouseX) / MOUSEDIV;
    angle_z = (double)(midY - mouseY) / MOUSEDIV;

    view.y += angle_z * 2;

    if((view.y - pos.y) > 8) view.y = pos.y + 8;
    if((view.y - pos.y) < -8) view.y = pos.y - 8;

    rotateCamera(-angle_y);
}

// Move forward or backwards.
// speed gives the speed at which the camera moves forward or backward.
// Positive values of speed moves forward. Negative values moves backward.
void Camera::moveCamera(double speed) {
    vec3 fwdv = view - pos;

    pos.x = pos.x + fwdv.x * speed;
    pos.z = pos.z + fwdv.z * speed;
    view.x = view.x + fwdv.x * speed;
    view.z = view.z + fwdv.z * speed;
}

// Move the camera side to side
// Positive values of speed move to the right.
// Negative values go to the left.
void Camera::strafeCamera(double speed) {
    vec3 fwdv = view - pos;
    
    pos.x = pos.x - fwdv.z * speed;
    pos.z = pos.z + fwdv.x * speed;
    view.x = view.x - fwdv.z * speed;
    view.z = view.z + fwdv.x * speed;
}

// Simply fly up and down.
// Positive values are up, negative values are down.
void Camera::flyCamera(double speed) {
    pos.y = pos.y + speed;
    view.y = view.y + speed;
}

// Rotate the camera. Apply a rotation matrix to the z and x coordinates.
void Camera::rotateCamera(double speed) {
    vec3 fwdv = view - pos;
    
    // Rotation matrix
    view.z = (double)(pos.z + sin(speed)*fwdv.x + cos(speed)*fwdv.z);
    view.x = (double)(pos.x + cos(speed)*fwdv.x - sin(speed)*fwdv.z);
}
