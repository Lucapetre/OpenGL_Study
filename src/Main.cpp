#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "glad.h"
#include "glfw3.h"
#include "Shader.h"
// glfw callbacks
// --------------
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
int main() {

    // glfw boilerplate
    // ----------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // for macOS add the line below
    // ----------------------------
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(2880, 1800, "OpenGL Study", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << '\n';
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    // load OpenGL functions
    // ---------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << '\n';
    }
    glViewport(0, 0, 2800, 1800);

    // vertex input
    // -----------
    float vertices[] = {
        // positions        // colors
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top right: red
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right: green
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left: blue
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // top left: yellow
   };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // vertex attributes linking
    // -------------------------
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // shader creating
    // ---------------

    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");
    shader.use();
    std::string uniformName = "testUniformColor";

    // render loop
    // ----------
    // the line below -> obtain a non filled rectangle
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window)) {
        // input processing
        // ---------------
        processInput(window);

        // update uniforms values
        // ----------------------
        float time = glfwGetTime();
        float greenValue = sin(time) + 1.0f;
        float redValue = cos(time) + 1.0f;
        float blueValue = (sin(time) + cos(time)) / 2.0f;
        shader.setVec3(uniformName, redValue, greenValue, blueValue);


        // rendering commands
        // --------------------
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // check and call events / buffer swaping
        // ---------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.deleteShader();
    glfwTerminate();
    return 0;
}


void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

}
