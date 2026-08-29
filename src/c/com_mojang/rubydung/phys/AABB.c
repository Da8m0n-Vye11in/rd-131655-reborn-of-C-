#include "com_mojang/rubydung/phys/AABB.h"
#include <stdlib.h>
#include <math.h>

AABB* AABB_new(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    AABB* a = (AABB*)malloc(sizeof(AABB));
    if (!a) return NULL;
    a->minX = minX; a->minY = minY; a->minZ = minZ;
    a->maxX = maxX; a->maxY = maxY; a->maxZ = maxZ;
    return a;
}

AABB* AABB_expand(const AABB* a, float x, float y, float z) {
    float minX = a->minX + (x < 0 ? x : 0);
    float minY = a->minY + (y < 0 ? y : 0);
    float minZ = a->minZ + (z < 0 ? z : 0);
    float maxX = a->maxX + (x > 0 ? x : 0);
    float maxY = a->maxY + (y > 0 ? y : 0);
    float maxZ = a->maxZ + (z > 0 ? z : 0);
    return AABB_new(minX, minY, minZ, maxX, maxY, maxZ);
}

void AABB_move(AABB* a, float x, float y, float z) {
    if (!a) return;
    a->minX += x; a->maxX += x;
    a->minY += y; a->maxY += y;
    a->minZ += z; a->maxZ += z;
}

static int overlapsOnYZ(const AABB* a, const AABB* b) {
    return !(a->maxY <= b->minY || a->minY >= b->maxY || a->maxZ <= b->minZ || a->minZ >= b->maxZ);
}

static int overlapsOnXZ(const AABB* a, const AABB* b) {
    return !(a->maxX <= b->minX || a->minX >= b->maxX || a->maxZ <= b->minZ || a->minZ >= b->maxZ);
}

static int overlapsOnXY(const AABB* a, const AABB* b) {
    return !(a->maxX <= b->minX || a->minX >= b->maxX || a->maxY <= b->minY || a->minY >= b->maxY);
}

float AABB_clipXCollide(const AABB* a, const AABB* other, float xa) {
    if (!a || !other) return xa;
    if (!overlapsOnYZ(a, other)) return xa;

    if (xa > 0.0f) {
        if (a->maxX <= other->minX) {
            float delta = other->minX - a->maxX;
            if (delta < xa) xa = delta;
        }
    } else if (xa < 0.0f) {
        if (a->minX >= other->maxX) {
            float delta = other->maxX - a->minX;
            if (delta > xa) xa = delta;
        }
    }
    return xa;
}

float AABB_clipYCollide(const AABB* a, const AABB* other, float ya) {
    if (!a || !other) return ya;
    if (!overlapsOnXZ(a, other)) return ya;

    if (ya > 0.0f) {
        if (a->maxY <= other->minY) {
            float delta = other->minY - a->maxY;
            if (delta < ya) ya = delta;
        }
    } else if (ya < 0.0f) {
        if (a->minY >= other->maxY) {
            float delta = other->maxY - a->minY;
            if (delta > ya) ya = delta;
        }
    }
    return ya;
}

float AABB_clipZCollide(const AABB* a, const AABB* other, float za) {
    if (!a || !other) return za;
    if (!overlapsOnXY(a, other)) return za;

    if (za > 0.0f) {
        if (a->maxZ <= other->minZ) {
            float delta = other->minZ - a->maxZ;
            if (delta < za) za = delta;
        }
    } else if (za < 0.0f) {
        if (a->minZ >= other->maxZ) {
            float delta = other->maxZ - a->minZ;
            if (delta > za) za = delta;
        }
    }
    return za;
}
