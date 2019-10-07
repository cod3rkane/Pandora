#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;

    updateVectors();
}

Camera::~Camera() {
    
}

void Camera::updateVectors() {
    glm::vec3 front;
    front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front.y = std::sin(glm::radians(pitch));
    front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::mouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    updateVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}
