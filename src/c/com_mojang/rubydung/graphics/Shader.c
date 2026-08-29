#include "com_mojang/rubydung/graphics/Shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_shader_log(GLuint shader) {
    GLint len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 1) {
        char* buf = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, NULL, buf);
        fprintf(stderr, "Shader log: %s\n", buf);
        free(buf);
    }
}

static void print_program_log(GLuint prog) {
    GLint len = 0;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 1) {
        char* buf = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, NULL, buf);
        fprintf(stderr, "Program log: %s\n", buf);
        free(buf);
    }
}

GLuint Shader_create_from_source(const char* vertex_src, const char* fragment_src) {
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertex_src, NULL);
    glCompileShader(vert);
    GLint ok = 0; glGetShaderiv(vert, GL_COMPILE_STATUS, &ok);
    if (!ok) { print_shader_log(vert); glDeleteShader(vert); return 0; }

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragment_src, NULL);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &ok);
    if (!ok) { print_shader_log(frag); glDeleteShader(vert); glDeleteShader(frag); return 0; }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) { print_program_log(prog); glDeleteShader(vert); glDeleteShader(frag); glDeleteProgram(prog); return 0; }

    glDetachShader(prog, vert); glDetachShader(prog, frag);
    glDeleteShader(vert); glDeleteShader(frag);
    return prog;
}

void Shader_use(GLuint program) {
    glUseProgram(program);
}

void Shader_set_vec3(GLuint program, const char* name, float x, float y, float z) {
    GLint loc = glGetUniformLocation(program, name);
    if (loc >= 0) glUniform3f(loc, x, y, z);
}

void Shader_set_int(GLuint program, const char* name, int value) {
    GLint loc = glGetUniformLocation(program, name);
    if (loc >= 0) glUniform1i(loc, value);
}
