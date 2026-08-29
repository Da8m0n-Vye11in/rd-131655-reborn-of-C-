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

#ifdef __cplusplus
}
#endif

#endif // LEVEL_H
