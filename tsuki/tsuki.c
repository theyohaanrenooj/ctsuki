#include "tsuki.h"

int tsuki_win_w;
int tsuki_win_h;
GLFWwindow* tsuki_win;

float pxToGlW(float w) {
    return (w/tsuki_win_w);
}
float pxToGlH(float h) {
    return (h/tsuki_win_h);
}
float pxToGlX(float x) {
    return (x/tsuki_win_w) * 2.0f -1.0f;
}
float pxToGlY(float y) {
    return (y/tsuki_win_h) * 2.0f -1.0f;
}


void checkShaderCompileErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];

    if (strcmp(type, "PROGRAM") != 0)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n",
                   type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- \n",
                   type, infoLog);
        }
    }
}
