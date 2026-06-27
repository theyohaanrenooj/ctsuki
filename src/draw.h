#include "tsuki.h"

#ifndef DRAW_H
#define DRAW_H

typedef struct {
    float x;
    float y;
    int offsetLoc;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int shaderProgram;
} Rect;

extern const char *vertexShaderSource;
extern const char *fragmentShaderSource; 

Rect createRect(float x,float y,float w,float h);
void drawRect(Rect *rect);
void deleteRect(Rect *rect);

#endif
