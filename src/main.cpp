#include <iostream>
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