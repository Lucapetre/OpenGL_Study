#ifndef OPENGL_STUDY_CAMERA_HPP
#define OPENGL_STUDY_CAMERA_HPP

#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    bool firstMouse = false;

private:
    glm::vec3 cameraPosition, cameraFront, cameraRight, cameraWorldUp, cameraUp;
    float yaw, pitch, fov = 45.0f, speed = 10.0f, sensitivity = 0.1f;

public:
    Camera(glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 cameraWorldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = - 90.0f, float pitch = 0.0f, float speed = 10.0f) {
        this->cameraPosition = cameraPosition;
        this->cameraWorldUp = cameraWorldUp;
        this->yaw = yaw;
        this->pitch = pitch;
        this->speed = speed;
        updateCameraVectors();
    }

private:
    void updateCameraVectors() {
        cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        cameraFront.y = sin(glm::radians(pitch));
        cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

        cameraFront = glm::normalize(cameraFront);
        cameraRight = glm::normalize(glm::cross(cameraFront, cameraWorldUp));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));

    }

public:
    void processMouseMovement(float xOffset, float yOffset) {
        yaw += xOffset * sensitivity;
        pitch += yOffset * sensitivity;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        updateCameraVectors();
    }

    float processMouseScroll(float yOffset) {
        fov -= yOffset;

        if (fov > 45.0f) fov = 45.0f;
        if (fov < 1.0f) fov = 1.0f;

        return fov;
    }

    void processKeyboard(unsigned int Key, float deltaTime) {
        float velocity = speed * deltaTime;

        if (Key == GLFW_KEY_W) cameraPosition += cameraFront * velocity;
        if (Key == GLFW_KEY_S) cameraPosition -= cameraFront * velocity;
        if (Key == GLFW_KEY_D) cameraPosition += cameraRight * velocity;
        if (Key == GLFW_KEY_A) cameraPosition -= cameraRight * velocity;
    }

    float getFov() {return fov;}

    glm::mat4 getViewMatrix() {return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);}

};


#endif //OPENGL_STUDY_CAMERA_HPP