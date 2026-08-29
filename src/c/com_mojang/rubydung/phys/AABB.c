#include "com_mojang/rubydung/phys/AABB.h"
#include <stdlib.h>

AABB* AABB_new(int minX, int minY, int minZ, int maxX, int maxY, int maxZ) {
    AABB* a = (AABB*)malloc(sizeof(AABB));
    if (!a) return NULL;
    a->minX = minX; a->minY = minY; a->minZ = minZ;
    a->maxX = maxX; a->maxY = maxY; a->maxZ = maxZ;
    return a;
}
