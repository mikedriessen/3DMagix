#pragma once

#include <glm/glm.hpp>

class Renderer {
public:
    static void Initialize();
    static void Shutdown();
    static void Clear();

    static void DrawCube(const glm::mat4& transform);
};
