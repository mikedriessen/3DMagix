#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Car.h"

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

        // Create a Car object
        Car car;

        // Main loop
        while (!window.ShouldClose()) {
            // Clear the screen
            Renderer::Clear();

            // Handle input
            bool moveForward = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS;
            bool moveBackward = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS;
            bool turnLeft = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS;
            bool turnRight = glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS;

            // Process car input
            car.ProcessInput(moveForward, moveBackward, turnLeft, turnRight);

            // Update car logic
            float deltaTime = 0.016f; // Approximate 60 FPS
            car.Update(deltaTime);

            // Create transformation matrix for the car
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), car.GetPosition());
            transform = glm::rotate(transform, car.GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));

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
