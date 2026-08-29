#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "com_mojang/rubydung/level/Textures.h"
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

void Textures_init(void) { /* no-op for now */ }

int Textures_loadTexture(const char* path, int filter) {
    int w, h, comp;
    unsigned char* data = stbi_load(path, &w, &h, &comp, 4);
    if (!data) {
        fprintf(stderr, "Failed to load image: %s\n", path);
        return -1;
    }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
    return (int)tex;
}
