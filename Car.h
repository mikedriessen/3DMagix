#pragma once

#include <glm/glm.hpp>

class Car {
public:
    Car();

    void Update(float deltaTime);
    void ProcessInput(bool moveForward, bool moveBackward, bool turnLeft, bool turnRight);

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;

private:
    glm::vec3 position;
    glm::vec3 rotation; // Yaw, Pitch, Roll
    float speed;
    float maxSpeed;
    float acceleration;
    float steeringAngle;
};
