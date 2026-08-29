#ifndef CHUNK_H
#define CHUNK_H

#include "com_mojang/rubydung/level/AABB.h"
#include "com_mojang/rubydung/level/Tessellator.h"
#include "com_mojang/rubydung/level/Level.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Chunk {
    Level* level;
    AABB* boundingBox;
    int minX, minY, minZ;
    int maxX, maxY, maxZ;
    int lists;
    int dirty;
} Chunk;

extern int Chunk_rebuiltThisFrame;
extern int Chunk_updates;

Chunk* Chunk_new(Level* level, int minX, int minY, int minZ, int maxX, int maxY, int maxZ);
void Chunk_rebuild(Chunk* chunk, int layer);
void Chunk_render(Chunk* chunk, int layer);
void Chunk_setDirty(Chunk* chunk);
void Chunk_free(Chunk* chunk);

#ifdef __cplusplus
}
#endif

#endif // CHUNK_H
