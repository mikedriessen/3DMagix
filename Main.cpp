#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Window.h"
#include "Renderer.h"

// Camera and car transformation parameters
glm::vec3 carPosition(0.0f, 0.0f, -10.0f); // Position set further away (along negative Z-axis)
float carRotationY = glm::radians(180.0f); // Rotation set to face away from the player (180 degrees)
float movementSpeed = 0.0005f; // Very slow movement speed
float rotationSpeed = 0.0005f; // Much slower rotation speed

int main() {
    try {
        // Create the window
        Window window(800, 600, "3D Car Game Engine");

        // Initialize OpenGL loader
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD.");
        }

        // Initialize Renderer
        Renderer::Initialize();

        // Enable depth testing for proper 3D rendering
        glEnable(GL_DEPTH_TEST);

        // Main loop
        while (!window.ShouldClose()) {
            // Clear the screen
            Renderer::Clear();

            // Handle input
            bool moveForward = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS;
            bool moveBackward = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS;
            bool moveLeft = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS;
            bool moveRight = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS;
            bool resetPosition = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_R) == GLFW_PRESS;

            bool rotateLeft = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_LEFT) == GLFW_PRESS;
            bool rotateRight = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS;

            // Reset position when 'R' is pressed
            if (resetPosition) {
                carPosition = glm::vec3(0.0f, 0.0f, -10.0f);  // Reset to a position further away
                carRotationY = glm::radians(180.0f);  // Reset rotation to face away from the player
            }

            // Calculate movement direction based on car's rotation
            glm::vec3 forwardDirection = glm::vec3(sinf(carRotationY), 0.0f, cosf(carRotationY));
            glm::vec3 rightDirection = glm::vec3(cosf(carRotationY), 0.0f, -sinf(carRotationY));

            // Move the car based on WASD (A/D keys swapped)
            if (moveForward) {
                carPosition += forwardDirection * movementSpeed;
            }
            if (moveBackward) {
                carPosition -= forwardDirection * movementSpeed;
            }
            if (moveLeft) {
                carPosition += rightDirection * movementSpeed; // Reversed: A goes to the right
            }
            if (moveRight) {
                carPosition -= rightDirection * movementSpeed; // Reversed: D goes to the left
            }

            // Rotate the car based on arrow keys (slower rotation)
            if (rotateLeft) {
                carRotationY += rotationSpeed;
            }
            if (rotateRight) {
                carRotationY -= rotationSpeed;
            }

            // Create transformation matrix for the car
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), carPosition);
            transform = glm::rotate(transform, carRotationY, glm::vec3(0.0f, 1.0f, 0.0f));

            // Render the car
            Renderer::DrawCube(transform);

            // Swap buffers and poll events
            glfwSwapBuffers(window.GetGLFWWindow());
            window.PollEvents();
        }

        // Shutdown Renderer
        Renderer::Shutdown();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
