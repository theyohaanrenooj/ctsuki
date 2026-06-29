#include "image.h"

tsukiTexture tsukiLoadTexture(char const *filename) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        printf("ERROR::TEXTURE::LOAD_FAILED: %s\n", filename);
    }

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return (tsukiTexture){tex, width, height};   
}

unsigned int tsukiLoadShader(const char *vertexPath, const char *fragmentPath) {
    unsigned int ID = 0;

    // 1) read files into memory
    char *vertexCode = NULL, *fragmentCode = NULL;

    FILE *vShaderFile = fopen(vertexPath, "rb");
    if (!vShaderFile) {
        printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
        return 0;
    }
    FILE *fShaderFile = fopen(fragmentPath, "rb");
    if (!fShaderFile) {
        fclose(vShaderFile);
        printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
        return 0;
    }

    fseek(vShaderFile, 0, SEEK_END);
    long vLen = ftell(vShaderFile);
    fseek(vShaderFile, 0, SEEK_SET);

    fseek(fShaderFile, 0, SEEK_END);
    long fLen = ftell(fShaderFile);
    fseek(fShaderFile, 0, SEEK_SET);

    if (vLen < 0 || fLen < 0) {
        fclose(vShaderFile);
        fclose(fShaderFile);
        printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
        return 0;
    }

    vertexCode = (char*)malloc((size_t)vLen + 1);
    fragmentCode = (char*)malloc((size_t)fLen + 1);
    if (!vertexCode || !fragmentCode) {
        fclose(vShaderFile);
        fclose(fShaderFile);
        free(vertexCode);
        free(fragmentCode);
        printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
        return 0;
    }

    size_t vRead = fread(vertexCode, 1, (size_t)vLen, vShaderFile);
    size_t fRead = fread(fragmentCode, 1, (size_t)fLen, fShaderFile);

    fclose(vShaderFile);
    fclose(fShaderFile);

    vertexCode[vRead] = '\0';
    fragmentCode[fRead] = '\0';

    if (vRead != (size_t)vLen || fRead != (size_t)fLen) {
        free(vertexCode);
        free(fragmentCode);
        printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
        return 0;
    }

    const char* vShaderCode = vertexCode;
    const char* fShaderCode = fragmentCode;

    // 2) compile shaders
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkShaderCompileErrors(vertex, "VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkShaderCompileErrors(fragment, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkShaderCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertexCode);
    free(fragmentCode);

    return ID;   
}
