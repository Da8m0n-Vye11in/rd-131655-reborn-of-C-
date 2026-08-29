#include "com_mojang/rubydung/level/LevelRenderer.h"
#include <stdlib.h>
#include <stdio.h>

LevelRenderer* LevelRenderer_new(Level* level) {
    LevelRenderer* lr = (LevelRenderer*)malloc(sizeof(LevelRenderer));
    if (!lr) return NULL;
    lr->level = level;
    lr->chunksX = (level->width + 15) / 16;
    lr->chunksY = (level->.height + 15) / 16;
    lr->chunksZ = (level->depth + 15) / 16;
    int total = lr->chunksX * lr->chunksY * lr->chunksZ;
    lr->chunks = (Chunk**)calloc(total, sizeof(Chunk*));
    if (!lr->chunks) { free(lr); return NULL; }

    int idx = 0;
    for (int x = 0; x < lr->chunksX; ++x) {
        for (int y = 0; y < lr->chunksY; ++y) {
            for (int z = 0; z < lr->chunksZ; ++z) {
                int minX = x*16; int minY = y*16; int minZ = z*16;
                int maxX = (minX+16 < level->width) ? minX+16 : level->width;
                int maxY = (minY+16 < level->height) ? minY+16 : level->height;
                int maxZ = (minZ+16 < level->depth) ? minZ+16 : level->depth;
                lr->chunks[idx++] = Chunk_new(level, minX, minY, minZ, maxX, maxY, maxZ);
            }
        }
    }
    return lr;
}

void LevelRenderer_render(LevelRenderer* lr, int layer) {
    if (!lr) return;
    int total = lr->chunksX * lr->chunksY * lr->chunksZ;
    for (int i = 0; i < total; ++i) {
        Chunk_render(lr->chunks[i], layer);
    }
}

void LevelRenderer_free(LevelRenderer* lr) {
    if (!lr) return;
    int total = lr->chunksX * lr->chunksY * lr->chunksZ;
    for (int i = 0; i < total; ++i) {
        if (lr->chunks[i]) Chunk_free(lr->chunks[i]);
    }
    free(lr->chunks);
    free(lr);
}
