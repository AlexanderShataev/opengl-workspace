#include "camera.h"

#include <iostream>

Camera::Camera()
{
}

void Camera::setSpeed(float speed) { speed_ = speed; }

void Camera::setCameraFront(glm::vec3 cameraFront)
{
    cameraFront_ = cameraFront;
}

void Camera::setCameraPos(glm::vec3 cameraPos) {
    cameraPos_ = cameraPos;
}

void Camera::setCameraUp(glm::vec3 cameraUp) {
    cameraUp_ = cameraUp;
}

void Camera::setCurrentFrameTime(float time) {
    deltaTime_ = time - lastFrame_;
    lastFrame_ = time;
}

void Camera::moveUp()
{
    cameraPos_ += getNormilizedSpeed() * cameraFront_;
}

void Camera::moveDown()
{
    cameraPos_ -= getNormilizedSpeed() * cameraFront_;
}

void Camera::moveRight()
{
    cameraPos_ += glm::normalize(glm::cross(cameraFront_, cameraUp_)) * getNormilizedSpeed();
}

void Camera::moveLeft()
{
    cameraPos_ -= glm::normalize(glm::cross(cameraFront_, cameraUp_)) * getNormilizedSpeed();
}

void Camera::setFront(float xpos, float ypos)
{
    if (firstMouse_)
    {
        lastX_ = xpos;
        lastY_ = ypos;
        firstMouse_ = false;
    }

    float xoffset = xpos - lastX_;
    float yoffset = lastY_ - ypos; // перевернуто, так как y-координаты идут снизу вверх
    lastX_ = xpos;
    lastY_ = ypos;

    float sensitivity = 0.1f; // измените это значение по своему усмотрению
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw_ += xoffset;
    pitch_ += yoffset;

    // Убеждаемся, что когда значение тангаж выходит за пределы, экран не переворачивается
    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    if (pitch_ < -89.0f)
        pitch_ = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    cameraFront_ = glm::normalize(front);
}

glm::mat4 Camera::lookAt() const
{
    return glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
}

float Camera::getNormilizedSpeed() const
{
    return speed_ * deltaTime_;
}

