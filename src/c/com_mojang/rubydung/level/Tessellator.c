#include "com_mojang/rubydung/level/Tessellator.h"
#include "com_mojang/rubydung/graphics/Shader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Simple embedded GLSL sources (core profile 330) */
static const char* VERT_SRC = "#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"layout(location=1) in vec2 aTex;\n"
"layout(location=2) in vec4 aCol;\n"
"uniform vec3 uScale;\n"
"uniform vec3 uOffset;\n"
"out vec2 vTex;\n"
"out vec4 vCol;\n"
"void main() {\n"
"    vec3 p = (aPos + uOffset) * uScale;\n"
"    gl_Position = vec4(p, 1.0);\n"
"    vTex = aTex;\n"
"    vCol = aCol;\n"
"}\n";

static const char* FRAG_SRC = "#version 330 core\n"
"in vec2 vTex;\n"
"in vec4 vCol;\n"
"out vec4 FragColor;\n"
"uniform sampler2D uTex;\n"
"void main() {\n"
"    vec4 t = texture(uTex, vTex);\n"
"    FragColor = t * vCol;\n"
"}\n";

static void ensure_capacity(Tessellator* t, int additional_floats) {
    if (!t->vertices) {
        t->capacity = additional_floats > 1024 ? additional_floats : 1024;
        t->vertices = (float*)malloc(sizeof(float) * t->capacity);
        t->vertex_count = 0;
        return;
    }
    int needed = (t->vertex_count * 9) + additional_floats;
    if (needed > t->capacity) {
        while (t->capacity < needed) t->capacity *= 2;
        t->vertices = (float*)realloc(t->vertices, sizeof(float) * t->capacity);
    }
}

void tessellator_init(Tessellator* t) {
    memset(t, 0, sizeof(Tessellator));
    glGenVertexArrays(1, &t->vao);
    glGenBuffers(1, &t->vbo);
    t->shader = Shader_create_from_source(VERT_SRC, FRAG_SRC);
    t->vertices = NULL;
    t->vertex_count = 0;
    t->capacity = 0;
    /* default transform */
    t->scale[0] = t->scale[1] = t->scale[2] = 1.0f;
    t->offset[0] = t->offset[1] = t->offset[2] = 0.0f;
    glBindVertexArray(t->vao);
    glBindBuffer(GL_ARRAY_BUFFER, t->vbo);
    /* allocate initially small buffer */
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
    /* attribute layout: vec3 pos, vec2 tex, vec4 color (9 floats) */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/* Adds a unit cube at integer position x,y,z. Each face uses full texture coordinates 0..1. */
void tessellator_add_cube(Tessellator* t, float x, float y, float z) {
    /* 36 vertices, 9 floats each => 324 floats */
    ensure_capacity(t, 36 * 9);
    /* cube corners */
    float x0 = x; float x1 = x + 1.0f;
    float y0 = y; float y1 = y + 1.0f;
    float z0 = z; float z1 = z + 1.0f;
    /* texture coords simple */
    float u0 = 0.0f, u1 = 1.0f, v0 = 0.0f, v1 = 1.0f;
    /* color white */
    float r=1.0f,g=1.0f,b=1.0f,a=1.0f;
    /* Helper to push one vertex */
    #define PUSH_VERTEX(px,py,pz,tu,tv) do { \
        int base = t->vertex_count * 9; \
        t->vertices[base+0] = (px); t->vertices[base+1] = (py); t->vertices[base+2] = (pz); \
        t->vertices[base+3] = (tu); t->vertices[base+4] = (tv); \
        t->vertices[base+5] = r; t->vertices[base+6] = g; t->vertices[base+7] = b; t->vertices[base+8] = a; \
        t->vertex_count++; \
    } while(0)

    /* +X face */
    PUSH_VERTEX(x1,y0,z0,u0,v1); PUSH_VERTEX(x1,y1,z0,u0,v0); PUSH_VERTEX(x1,y1,z1,u1,v0);
    PUSH_VERTEX(x1,y0,z0,u0,v1); PUSH_VERTEX(x1,y1,z1,u1,v0); PUSH_VERTEX(x1,y0,z1,u1,v1);
    /* -X face */
    PUSH_VERTEX(x0,y0,z1,u0,v1); PUSH_VERTEX(x0,y1,z1,u0,v0); PUSH_VERTEX(x0,y1,z0,u1,v0);
    PUSH_VERTEX(x0,y0,z1,u0,v1); PUSH_VERTEX(x0,y1,z0,u1,v0); PUSH_VERTEX(x0,y0,z0,u1,v1);
    /* +Y face */
    PUSH_VERTEX(x0,y1,z0,u0,v1); PUSH_VERTEX(x1,y1,z0,u1,v1); PUSH_VERTEX(x1,y1,z1,u1,v0);
    PUSH_VERTEX(x0,y1,z0,u0,v1); PUSH_VERTEX(x1,y1,z1,u1,v0); PUSH_VERTEX(x0,y1,z1,u0,v0);
    /* -Y face */
    PUSH_VERTEX(x0,y0,z1,u0,v1); PUSH_VERTEX(x1,y0,z1,u1,v1); PUSH_VERTEX(x1,y0,z0,u1,v0);
    PUSH_VERTEX(x0,y0,z1,u0,v1); PUSH_VERTEX(x1,y0,z0,u1,v0); PUSH_VERTEX(x0,y0,z0,u0,v0);
    /* +Z face */
    PUSH_VERTEX(x0,y0,z1,u0,v1); PUSH_VERTEX(x0,y1,z1,u0,v0); PUSH_VERTEX(x1,y1,z1,u1,v0);
    PUSH_VERTEX(x0,y0,z1,u0,v1); PUSH_VERTEX(x1,y1,z1,u1,v0); PUSH_VERTEX(x1,y0,z1,u1,v1);
    /* -Z face */
    PUSH_VERTEX(x1,y0,z0,u0,v1); PUSH_VERTEX(x1,y1,z0,u0,v0); PUSH_VERTEX(x0,y1,z0,u1,v0);
    PUSH_VERTEX(x1,y0,z0,u0,v1); PUSH_VERTEX(x0,y1,z0,u1,v0); PUSH_VERTEX(x0,y0,z0,u1,v1);

    #undef PUSH_VERTEX
}

void tessellator_set_transform(Tessellator* t, float sx, float sy, float sz, float ox, float oy, float oz) {
    t->scale[0]=sx; t->scale[1]=sy; t->scale[2]=sz;
    t->offset[0]=ox; t->offset[1]=oy; t->offset[2]=oz;
}

void tessellator_flush(Tessellator* t) {
    if (!t || t->vertex_count == 0) return;
    glBindVertexArray(t->vao);
    glBindBuffer(GL_ARRAY_BUFFER, t->vbo);
    size_t floats = (size_t)t->vertex_count * 9;
    glBufferData(GL_ARRAY_BUFFER, floats * sizeof(float), t->vertices, GL_DYNAMIC_DRAW);

    Shader_use(t->shader);
    Shader_set_vec3(t->shader, "uScale", t->scale[0], t->scale[1], t->scale[2]);
    Shader_set_vec3(t->shader, "uOffset", t->offset[0], t->offset[1], t->offset[2]);
    Shader_set_int(t->shader, "uTex", 0);

    glActiveTexture(GL_TEXTURE0);
    /* Assume texture already bound by caller (Chunk/Textures) */

    glDrawArrays(GL_TRIANGLES, 0, t->vertex_count);

    /* reset */
    t->vertex_count = 0;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
