#ifndef TESSELLATOR_H
#define TESSELLATOR_H

#include <glad/glad.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tessellator {
    GLuint vao;
    GLuint vbo;
    GLuint shader;
    float* vertices; /* interleaved: x,y,z,u,v,r,g,b,a */
    int vertex_count; /* number of vertices (not floats) */
    int capacity; /* floats capacity */
    float scale[3];
    float offset[3];
} Tessellator;

void tessellator_init(Tessellator* t);
void tessellator_add_cube(Tessellator* t, float x, float y, float z);
void tessellator_flush(Tessellator* t);
void tessellator_set_transform(Tessellator* t, float sx, float sy, float sz, float ox, float oy, float oz);

#ifdef __cplusplus
}
#endif

#endif // TESSELLATOR_H
