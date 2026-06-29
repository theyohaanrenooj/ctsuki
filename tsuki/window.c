#include "window.h"

void framebufSizeCallback(GLFWwindow *window,int w, int h) {
    glViewport(0,0,w,h);    
}

int initTsuki(const char* title) {
    if (!glfwInit()) {printf("glfw failed it initialize\n"); return -1;};
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    tsuki_win_w = 800;
    tsuki_win_h = 600;
    tsuki_win = glfwCreateWindow(tsuki_win_w,tsuki_win_h,title,NULL,NULL);
    if (tsuki_win == NULL) {
        printf("failed to create window!\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(tsuki_win);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        glfwDestroyWindow(tsuki_win);
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(tsuki_win, framebufSizeCallback);

    return 0;
}

void runTsuki(void (*input)(),void (*draw)()) {
     while(!glfwWindowShouldClose(tsuki_win)) {
         input();

         draw();

         glfwSwapBuffers(tsuki_win);
         glfwPollEvents();
    }

}
