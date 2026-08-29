#include "com_mojang/rubydung/level/Level.h"
#include <stdlib.h>

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
