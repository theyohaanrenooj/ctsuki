#include "draw.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform vec2 uOffset;\n"
    "void main()\n"
    "{\n"
    "   vec3 pos = aPos;\n"
    "   pos.xy += uOffset;\n"
    "   gl_Position = vec4(pos, 1.0);\n"
    "}\n\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

Rect createRect(float x, float y,float w,float h) {
    unsigned int VBO, VAO, EBO;
    unsigned int shaderProgram;
    int offsetLoc;

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    offsetLoc = glGetUniformLocation(shaderProgram, "uOffset");

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float wi = pxToGl(w,(float)tsuki_win_w);
    float he = pxToGl(h,(float)tsuki_win_h);
    float vertices[] = {
         wi,  he, 0.0f,  // top right
         wi, -he, 0.0f,  // bottom right
        -wi, -he, 0.0f,  // bottom left
        -wi,  he, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    Rect rect = {x,y,offsetLoc,VAO,VBO,EBO,shaderProgram};

    return rect;
}

void drawRect(Rect *rect) {
    glUseProgram(rect->shaderProgram);
    glUniform2f(rect->offsetLoc, pxToGl(rect->x, (float)tsuki_win_w), pxToGl(rect->y, (float)tsuki_win_h));
    glBindVertexArray(rect->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
}

void deleteRect(Rect *rect) {
    glDeleteVertexArrays(1, &(rect->VAO));
    glDeleteBuffers(1, &(rect->VBO));
    glDeleteBuffers(1, &(rect->EBO));
    glDeleteProgram(rect->shaderProgram);
}
