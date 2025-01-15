#include "Window.h"
#include <stdexcept>

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
        });
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::PollEvents() const {
    glfwPollEvents();
}

GLFWwindow* Window::GetGLFWWindow() const {
    return window;
}
