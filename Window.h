#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool ShouldClose() const;
    void PollEvents() const;
    GLFWwindow* GetGLFWWindow() const;

private:
    GLFWwindow* window;
};
