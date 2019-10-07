#ifndef CGAME_CAMERA_H
#define CGAME_CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    void updateVectors();
    void mouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    glm::mat4 getViewMatrix();
    ~Camera();
};

#endif // CGAME_CAMERA_H
