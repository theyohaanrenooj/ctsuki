#include "tsuki.h"

#ifndef WINDOW_H
#define WINDOW_H

void framebufSizeCallback(GLFWwindow* window,int w,int h);
int initTsuki(const char* title);
void runTsuki(void (*input)(),void (*draw)());

#endif
