#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
public:
    Camera();
    void setSpeed(float speed);

    void setCameraFront(glm::vec3 cameraFront);
    void setCameraPos(glm::vec3 cameraPos);
    void setCameraUp(glm::vec3 cameraUp);

    void setCurrentFrameTime(float time);

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void setFront(float x, float y);

    glm::mat4 lookAt() const;

private:
    float getNormilizedSpeed() const;

    float speed_ = 0;
    glm::vec3 cameraPos_;
    glm::vec3 cameraUp_;
    glm::vec3 cameraFront_;
    glm::mat4 lookAtM;

    bool firstMouse_ = true;
    float yaw_ = -90.0f;	// рыскание инициализируется значением -90.0 градусов, так как значние рыскания равное 0.0 приводит к тому, что вектор направления будет указывать вправо, поэтому мы изначально поворачиваемся немного влево
    float pitch_ = 0.0f;
    float lastX_ = 800.0f / 2.0;
    float lastY_ = 600.0 / 2.0;
    float fov_ = 45.0f;

    float deltaTime_ = 0.0f;	// время между текущим кадром и последним кадром
    float lastFrame_ = 0.0f;

};

#endif // CAMERA_H
