#ifndef LEVEL_H
#define LEVEL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Level Level;

struct Level {
    int width, height, depth;
    int (*isTile)(Level* level, int x, int y, int z);
    float (*getBrightness)(Level* level, int x, int y, int z);
};

Level* Level_new(int width, int height, int depth);
void Level_free(Level* l);

/* Returns an array of AABB* for tiles intersecting box. The caller must free the AABB* array and each AABB via free(). */
struct AABB** Level_getCubes(Level* level, const struct AABB* box, int* outCount);

#ifdef __cplusplus
}
#endif

#endif // LEVEL_H
