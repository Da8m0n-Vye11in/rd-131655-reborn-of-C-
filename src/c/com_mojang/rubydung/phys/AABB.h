#ifndef AABB_H
#define AABB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AABB {
    float minX, minY, minZ;
    float maxX, maxY, maxZ;
} AABB;

AABB* AABB_new(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
AABB* AABB_expand(const AABB* a, float x, float y, float z);
void AABB_move(AABB* a, float x, float y, float z);

/* Collision clip: given this AABB (world block) and other (moving box), compute new delta (xa/ya/za) to avoid overlap */
float AABB_clipXCollide(const AABB* a, const AABB* other, float xa);
float AABB_clipYCollide(const AABB* a, const AABB* other, float ya);
float AABB_clipZCollide(const AABB* a, const AABB* other, float za);

#ifdef __cplusplus
}
#endif

#endif // AABB_H
