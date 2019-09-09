#include "geometry.h"
#include <glad/glad.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::unordered_map<GLenum, unsigned long> typeSize{{GL_FLOAT,sizeof(float)},
                                                   {GL_INT,sizeof(int)},
                                                   {GL_BOOL,sizeof(bool)}};



unsigned int calculateStride(const std::vector<VertexAttribute>& attributes)
{
    unsigned int stride = 0;
    for (const auto& attribute : attributes)
    {
        stride += (attribute.numElements * typeSize[attribute.type]);
    }
    return stride;
}

Geometry::Geometry(const std::vector<float>& data, const std::vector<VertexAttribute>& attributes)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), data.data(), GL_STATIC_DRAW);

    // Declare attribute pointers
    unsigned int index = 0;
    unsigned int startingPosition = 0;
    unsigned int stride = calculateStride(attributes);

    for (const auto& attribute : attributes)
    {
        glVertexAttribPointer(index, attribute.numElements, attribute.type, attribute.normalized, stride, (void*)startingPosition);
        glEnableVertexAttribArray(index);

        index++;
        startingPosition += (attribute.numElements*typeSize[attribute.type]);
    }
    
    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

Geometry::Geometry(const std::vector<float>& vertices, const std::vector<unsigned int>&  indices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}


void Geometry::draw(const Shader& shader)
{
    glBindVertexArray(VAO);

    glUseProgram(shader.ID);
    
    EBO ? glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0) :
          glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0); 
}

Geometry::~Geometry()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}