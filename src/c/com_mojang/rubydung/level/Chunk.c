#include "com_mojang/rubydung/level/Chunk.h"
#include "com_mojang/rubydung/level/Textures.h"
#include "com_mojang/rubydung/level/Tile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glad/glad.h>

static int TEXTURE_ID = -1;
static Tessellator TESSELLATOR_INSTANCE;

int Chunk_rebuiltThisFrame = 0;
int Chunk_updates = 0;

Chunk* Chunk_new(Level* level, int minX, int minY, int minZ, int maxX, int maxY, int maxZ) {
    Chunk* c = (Chunk*)malloc(sizeof(Chunk));
    if (!c) return NULL;
    c->level = level;
    c->minX = minX; c->minY = minY; c->minZ = minZ;
    c->maxX = maxX; c->maxY = maxY; c->maxZ = maxZ;
    c->lists = 0; /* display lists deprecated; store 0 */
    c->dirty = 1;
    c->boundingBox = AABB_new(minX, minY, minZ, maxX, maxY, maxZ);

    if (TEXTURE_ID == -1) {
        TEXTURE_ID = Textures_loadTexture("resources/terrain.png", GL_NEAREST);
    }
    return c;
}

void Chunk_rebuild(Chunk* chunk, int layer) {
    if (!chunk) return;
    if (Chunk_rebuiltThisFrame == 2) return;
    Chunk_updates++;
    Chunk_rebuiltThisFrame++;
    chunk->dirty = 0;

    tessellator_init(&TESSELLATOR_INSTANCE);

    for (int x = chunk->minX; x < chunk->maxX; ++x) {
        for (int y = chunk->minY; y < chunk->maxY; ++y) {
            for (int z = chunk->minZ; z < chunk->maxZ; ++z) {
                int isTile = chunk->level->isTile(chunk->level, x, y, z);
                float brightness = chunk->level->getBrightness(chunk->level, x, y, z);
                if (isTile) {
                    if (y > chunk->level->depth - 7 && brightness == 1.0f) {
                        Tile_render_grass(&TESSELLATOR_INSTANCE, chunk->level, layer, x, y, z);
                    } else {
                        Tile_render_rock(&TESSELLATOR_INSTANCE, chunk->level, layer, x, y, z);
                    }
                }
            }
        }
    }
    tessellator_flush(&TESSELLATOR_INSTANCE);
}

void Chunk_render(Chunk* chunk, int layer) {
    if (!chunk) return;
    if (chunk->dirty) {
        Chunk_rebuild(chunk, 0);
        Chunk_rebuild(chunk, 1);
    }
    /* No display lists; render directly via tessellator (no-op) */
}

void Chunk_setDirty(Chunk* chunk) {
    if (!chunk) return; chunk->dirty = 1;
}

void Chunk_free(Chunk* chunk) {
    if (!chunk) return;
    if (chunk->boundingBox) free(chunk->boundingBox);
    free(chunk);
}
