#ifndef LEVELRENDERER_H
#define LEVELRENDERER_H

#include "com_mojang/rubydung/level/Level.h"
#include "com_mojang/rubydung/level/Chunk.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LevelRenderer {
    Level* level;
    Chunk** chunks;
    int chunksX, chunksY, chunksZ;
} LevelRenderer;

LevelRenderer* LevelRenderer_new(Level* level);
void LevelRenderer_render(LevelRenderer* lr, int layer);
void LevelRenderer_free(LevelRenderer* lr);

#ifdef __cplusplus
}
#endif

#endif // LEVELRENDERER_H
