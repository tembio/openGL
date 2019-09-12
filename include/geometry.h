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

    Geometry(const std::vector<float>& data,
             const std::vector<VertexAttribute>& attributes,
             GLenum bufferUsageMode = GL_STATIC_DRAW);

    Geometry(const std::vector<float>& data,
             const std::vector<unsigned int>&  indices,
             const std::vector<VertexAttribute>& attributes,
             GLenum bufferUsageMode = GL_STATIC_DRAW);

    void draw(const Shader& shader, GLenum primitiveToDraw = GL_TRIANGLES);

    ~Geometry();
  private:
    unsigned int VBO, VAO, EBO=0;
    unsigned int numElementsToDraw;
};