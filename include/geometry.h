#pragma once

#include <glad/glad.h>
#include "shader.h"
#include <vector>

struct VertexAttribute{
    unsigned int numElements = 3;
    GLenum type = GL_FLOAT;
    GLboolean normalized = GL_FALSE;
};

class Geometry{
  public:
    Geometry() = delete;
    Geometry(const std::vector<float>& data, const std::vector<VertexAttribute>& attributes);
    Geometry(const std::vector<float>& vertices, const std::vector<unsigned int>&  indices);
    void draw(const Shader& shader);
    ~Geometry();
  private:
    unsigned int VBO, VAO, EBO=0;

};