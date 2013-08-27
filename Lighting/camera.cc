#include "main.h"
#include "camera.h"

#define MOUSEDIV 500 //originally 1000

void Camera::setCameraPosition(float pos_x, float pos_y, float pos_z,
			                   float view_x, float view_y, float view_z,
			                   float up_x, float up_y, float up_z)
{
	mPos = tVector3(pos_x, pos_y, pos_z);
	mView = tVector3(view_x, view_y, view_z);
	mUp = tVector3(up_x, view_y, view_z);
}

void Camera::moveMouse()
{
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

	mView.y += angle_z * 2;

	if((mView.y - mPos.y) > 8) mView.y = mPos.y + 8;
	if((mView.y - mPos.y) < -8) mView.y = mPos.y - 8;

	rotateCamera(-angle_y);
}

void Camera::moveCamera(float speed)
{
	tVector3 vVector = mView - mPos;

	mPos.x = mPos.x + vVector.x * speed;
	mPos.z = mPos.z + vVector.z * speed;
	mView.x = mView.x + vVector.x * speed;
	mView.z = mView.z + vVector.z * speed;
}

void Camera::strafeCamera(float speed)
{
	tVector3 vVector = mView - mPos;
	
	mPos.x = mPos.x - vVector.z * speed;
	mPos.z = mPos.z + vVector.x * speed;
	mView.x = mView.x - vVector.z * speed;
	mView.z = mView.z + vVector.x * speed;
}

void Camera::flyCamera(float speed)
{
    mPos.y = mPos.y + speed;
    mView.y = mView.y + speed;
}

void Camera::rotateCamera(float speed)
{
	tVector3 vVector = mView - mPos;
	
    mView.z = (float)(mPos.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
    mView.x = (float)(mPos.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}
