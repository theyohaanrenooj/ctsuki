#include "tsuki.h"
#include "draw.h"

void input();
void draw();

Rect rect;

int main(int argc, char *argv[]) {

    if (initTsuki("sup") != 0) {return -1;}

    rect = createRect(10.0f,10.0f,32.0f,32.0f);

    // running game loop
    runTsuki(*input,*draw);

    deleteRect(&rect);
    glfwTerminate();
    return 0;
}

void input() {
    if(glfwGetKey(tsuki_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(tsuki_win, true);
    if (glfwGetKey(tsuki_win, GLFW_KEY_W) == GLFW_PRESS)
        rect.y += 10.0f;
    if (glfwGetKey(tsuki_win, GLFW_KEY_S) == GLFW_PRESS)
        rect.y -= 10.0f;
    if (glfwGetKey(tsuki_win, GLFW_KEY_A) == GLFW_PRESS)
        rect.x -= 10.0f;
    if (glfwGetKey(tsuki_win, GLFW_KEY_D) == GLFW_PRESS)
        rect.x += 10.0f;
}

void draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawRect(&rect);
}
