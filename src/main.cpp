#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"
#include "shader.h"
#include "geometry.h"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    initializeGLFW();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("shaders/shader.vs", "shaders/shader.fs");


    // 1 Attributes
    // std::vector<float> triangleVertices{
    //     -0.5f, -0.5f, 0.0f, // left  
    //      0.5f, -0.5f, 0.0f, // right 
    //      0.0f,  0.5f, 0.0f  // top   
    // }; 
    // VertexAttribute vertAttr;
    // Geometry triangle(triangleVertices, {vertAttr});


    // 2 Attributes
    std::vector<float> triangleVerticesWithColor{
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left  + red 
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right + green
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top   + blue
    }; 
    VertexAttribute vertAttr, colorAttr;
    Geometry triangle(triangleVerticesWithColor, {vertAttr, colorAttr});


    // Using VBO
    //     std::vector<float> vertices{
    //      0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left 
    // };
    // std::vector<unsigned int> indices{ 
    //     0, 1, 3,  // first Triangle
    //     1, 2, 3   // second Triangle
    // };
    // Geometry square(vertices, indices);


    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw geometry
        // square.draw(shader);
        triangle.draw(shader);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

