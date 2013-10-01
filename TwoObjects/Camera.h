#ifndef CAMERA_H
#define CAMERA_H

//#define WINSIZEX 1600
//#define WINSIZEY 1200
//#define WINSIZEX 2560
//#define WINSIZEY 1024
#define WINSIZEX 1024 
#define WINSIZEY 768 

class Camera {
public:
    void setCameraPosition(
            float pos_x, float pos_y, float pos_z,
            float view_x, float view_y, float view_z,
            float up_x, float up_y, float up_z);

    void moveMouse();
    void moveCamera(float speed);
    void strafeCamera(float speed);
    void flyCamera(float speed);
    void rotateCamera(float speed);

    Vector3 pos;
    Vector3 view;
    Vector3 up;
};

#endif
