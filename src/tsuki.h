#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

#include "utils.h"

#ifndef TSUKI_H
#define TSUKI_H

extern int tsuki_win_w;
extern int tsuki_win_h;
extern GLFWwindow* tsuki_win;

void framebufSizeCallback(GLFWwindow* window,int w,int h);
int initTsuki(const char* title);
void runTsuki(void (*input)(),void (*draw)());

#endif
