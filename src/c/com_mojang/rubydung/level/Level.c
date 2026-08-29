#include "com_mojang/rubydung/level/Level.h"
#include "com_mojang/rubydung/phys/AABB.h"
#include <stdlib.h>
#include <math.h>

static int default_isTile(Level* level, int x, int y, int z) {
    (void)level; (void)x; (void)z;
    return (y >= 0 && y < level->depth) ? 1 : 0;
}

static float default_getBrightness(Level* level, int x, int y, int z) {
    (void)level; (void)x; (void)y; (void)z;
    return 1.0f;
}

Level* Level_new(int width, int height, int depth) {
    Level* l = (Level*)malloc(sizeof(Level));
    if (!l) return NULL;
    l->width = width; l->height = height; l->depth = depth;
    l->isTile = default_isTile;
    l->getBrightness = default_getBrightness;
    return l;
}

void Level_free(Level* l) {
    if (!l) return; free(l);
}

struct AABB** Level_getCubes(Level* level, const struct AABB* box, int* outCount) {
    if (!level || !box || !outCount) return NULL;
    int minX = (int)floorf(box->minX);
    int maxX = (int)floorf(box->maxX);
    int minY = (int)floorf(box->minY);
    int maxY = (int)floorf(box->maxY);
    int minZ = (int)floorf(box->minZ);
    int maxZ = (int)floorf(box->maxZ);

    int capacity = 16;
    struct AABB** list = (struct AABB**)malloc(sizeof(struct AABB*) * capacity);
    int count = 0;

    for (int x = minX; x <= maxX; ++x) {
        for (int y = minY; y <= maxY; ++y) {
            for (int z = minZ; z <= maxZ; ++z) {
                if (level->isTile(level, x, y, z)) {
                    if (count >= capacity) {
                        capacity *= 2;
                        list = (struct AABB**)realloc(list, sizeof(struct AABB*) * capacity);
                    }
                    list[count++] = AABB_new((float)x, (float)y, (float)z, (float)(x+1), (float)(y+1), (float)(z+1));
                }
            }
        }
    }

    *outCount = count;
    return list;
}
