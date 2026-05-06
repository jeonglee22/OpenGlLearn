#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "윈도우 생성 실패\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD 초기화
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD 초기화 실패\n";
        return -1;
    }

    int  success;
    char infoLog[512];

    Shader ourShader("src/shaders/ex1.vshader", "src/shaders/ex1.fshader");

    float vertices1[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top  
    };

    // float vertices2[] = {
    //      0.5f,  0.5f, 0.0f,  
    //      0.1f, -0.5f, 0.0f, 
    //      0.9f, -0.5f, 0.0f, 
    // };

    unsigned int VAO1;
    // unsigned int EBO;
    glGenVertexArrays(1, &VAO1);
    // glGenVertexArrays(1, &VAO2);
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    // glGenBuffers(1, &VBO2);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glBindVertexArray(VAO2);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0); 

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 렌더 루프
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        // float timeValue = glfwGetTime();
        // float greenValue = sin(timeValue) / 2.0f + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // glUseProgram(shaderProgram2);
        // glBindVertexArray(VAO2);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    // glDeleteVertexArrays(1, &VBO2);
    glDeleteBuffers(1, &VBO1);
    // glDeleteBuffers(1, &VBO2);
    // glDeleteProgram(shaderProgram);
    // glDeleteProgram(shaderProgram2);

    glfwTerminate();
    return 0;
}