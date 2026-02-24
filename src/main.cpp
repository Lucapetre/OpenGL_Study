#include <iostream>
#include <fstream>
#include <sstream>
#include "glad.h"
#include "glfw3.h"

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
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f, 0.5f, 0.0f
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // vertex attributes linking
    // -------------------------
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    // vertex shader code
    // ------------------
    std::ifstream vertexShaderFile("../shaders/shader.vert");
    std::stringstream vertexShaderBuffer;
    vertexShaderBuffer << vertexShaderFile.rdbuf();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderCode = vertexShaderBuffer.str();
    const char* vertexSourceCode = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
    glCompileShader(vertexShader);

    // fragment shader code
    // --------------------
    std::ifstream fragmentShaderFile("../shaders/shader.frag");
    std::stringstream fragmentShaderBuffer;
    fragmentShaderBuffer << fragmentShaderFile.rdbuf();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderCode = fragmentShaderBuffer.str();
    const char* fragmentSourceCode = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
    glCompileShader(fragmentShader);

    // shader program code
    // -------------------
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // render loop
    // ----------
    while (!glfwWindowShouldClose(window)) {
        // input processing
        // ---------------
        processInput(window);

        // rendering commands
        // --------------------
        glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events / buffer swaping
        // ---------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

}