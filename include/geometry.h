#pragma once

#include <glad/glad.h>
#include "shader.h"
#include <vector>


class Geometry{
  public:
    Geometry() = delete;
    Geometry(const std::vector<float>& vertices);
    Geometry(const std::vector<float>& vertices, const std::vector<unsigned int>&  indices);
    void draw(const Shader& shader);
    ~Geometry();
  private:
    unsigned int VBO, VAO, EBO=0;

};