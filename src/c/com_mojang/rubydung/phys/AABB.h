#ifndef AABB_H
#define AABB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AABB {
    int minX, minY, minZ;
    int maxX, maxY, maxZ;
} AABB;

AABB* AABB_new(int minX, int minY, int minZ, int maxX, int maxY, int maxZ);

#ifdef __cplusplus
}
#endif

#endif // AABB_H
