#include "Car.h"

Car::Car()
    : position(0.0f), rotation(0.0f), speed(0.0f), maxSpeed(10.0f), acceleration(5.0f), steeringAngle(0.0f) {
}

void Car::Update(float deltaTime) {
    // Update position based on speed and direction
    position += glm::vec3(glm::cos(rotation.y), 0.0f, glm::sin(rotation.y)) * speed * deltaTime;

    // Apply simple drag to slow down the car when not accelerating
    speed *= 0.98f; // Adjust drag factor as needed
}

void Car::ProcessInput(bool moveForward, bool moveBackward, bool turnLeft, bool turnRight) {
    if (moveForward) {
        speed += acceleration * 0.01f; // Acceleration step
        if (speed > maxSpeed) speed = maxSpeed;
    }
    if (moveBackward) {
        speed -= acceleration * 0.01f;
        if (speed < -maxSpeed / 2) speed = -maxSpeed / 2; // Reverse has lower max speed
    }
    if (turnLeft) {
        rotation.y += 0.05f; // Adjust turning speed as needed
    }
    if (turnRight) {
        rotation.y -= 0.05f;
    }
}

glm::vec3 Car::GetPosition() const {
    return position;
}

glm::vec3 Car::GetRotation() const {
    return rotation;
}
