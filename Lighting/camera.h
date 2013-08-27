#define WINSIZEX 1280
#define WINSIZEY 800

class Camera
{
public:
        void setCameraPosition(float pos_x, float pos_y, float pos_z,
                               float view_x, float view_y, float view_z,
                               float up_x, float up_y, float up_z);

        void moveMouse();
        void moveCamera(float speed);
        void strafeCamera(float speed);
        void flyCamera(float speed);
        void rotateCamera(float speed);

        tVector3 mPos;
        tVector3 mView;
        tVector3 mUp;
};
