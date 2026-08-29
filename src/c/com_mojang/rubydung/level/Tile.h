#ifndef TILE_H
#define TILE_H

#include "com_mojang/rubydung/level/Tessellator.h"
#include "com_mojang/rubydung/level/Level.h"

#ifdef __cplusplus
extern "C" {
#endif

void Tile_render_grass(Tessellator* t, Level* level, int layer, int x, int y, int z);
void Tile_render_rock(Tessellator* t, Level* level, int layer, int x, int y, int z);

#ifdef __cplusplus
}
#endif

#endif // TILE_H
