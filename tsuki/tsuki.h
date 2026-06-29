#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <string.h>
#include "deps/stb_image.h"

#ifndef UTILS_H
#define UTILS_H

// window
extern int tsuki_win_w;
extern int tsuki_win_h;
extern GLFWwindow* tsuki_win;


// image
typedef struct {
    unsigned int data;
    int width;
    int height;
} tsukiTexture;

// entity
typedef struct {
    tsukiTexture tex;
    float x;
    float y;
    unsigned int shader;
    unsigned int VAO;
} tsukiEntity;

// basics
float pxToGlX(float x);
float pxToGlY(float y);
float pxToGlW(float w);
float pxToGlH(float h);
void checkShaderCompileErrors(unsigned int shader, const char* type);

#endif
