#include "main.h"
#include "camera.h"

#define MOUSEDIV 500 //originally 1000

void Camera::setCameraPosition(
        float pos_x, float pos_y, float pos_z,
        float view_x, float view_y, float view_z,
        float up_x, float up_y, float up_z) {
    pos = Vector3(pos_x, pos_y, pos_z);
    view = Vector3(view_x, view_y, view_z);
    up = Vector3(up_x, view_y, view_z);
}

void Camera::moveMouse() {
    int mouseX;
    int mouseY;
    int width = WINSIZEX;
    int height = WINSIZEY;
    int midX = width >> 1;
    int midY = height >> 1;
    float angle_y = 0.0f;
    float angle_z = 0.0f;

    SDL_GetMouseState(&mouseX, &mouseY);

    if((mouseX == midX) && (mouseY == midY)) return;

    SDL_WarpMouse(midX, midY);

    angle_y = (float)(midX - mouseX) / MOUSEDIV;
    angle_z = (float)(midY - mouseY) / MOUSEDIV;

    view.y += angle_z * 2;

    if((view.y - pos.y) > 8) view.y = pos.y + 8;
    if((view.y - pos.y) < -8) view.y = pos.y - 8;

    rotateCamera(-angle_y);
}

void Camera::moveCamera(float speed) {
    Vector3 v = view - pos;

    pos.x = pos.x + v.x * speed;
    pos.z = pos.z + v.z * speed;
    view.x = view.x + v.x * speed;
    view.z = view.z + v.z * speed;
}

void Camera::strafeCamera(float speed) {
    Vector3 v = view - pos;
    
    pos.x = pos.x - v.z * speed;
    pos.z = pos.z + v.x * speed;
    view.x = view.x - v.z * speed;
    view.z = view.z + v.x * speed;
}

void Camera::flyCamera(float speed) {
    pos.y = pos.y + speed;
    view.y = view.y + speed;
}

void Camera::rotateCamera(float speed) {
    Vector3 v = view - pos;
    
    view.z = (float)(pos.z + sin(speed)*v.x + cos(speed)*v.z);
    view.x = (float)(pos.x + cos(speed)*v.x - sin(speed)*v.z);
}
