#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

GLuint Shader_create_from_source(const char* vertex_src, const char* fragment_src);
void Shader_use(GLuint program);
void Shader_set_vec3(GLuint program, const char* name, float x, float y, float z);
void Shader_set_int(GLuint program, const char* name, int value);

#ifdef __cplusplus
}
#endif

#endif // SHADER_H
