#include "tsuki.h"

#ifndef IMAGE_H
#define IMAGE_H

tsukiTexture tsukiLoadTexture(char const *filename);
unsigned int tsukiLoadShader(const char* vertexPath, const char* fragmentPath);

#endif
