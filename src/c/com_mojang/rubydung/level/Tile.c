#include "com_mojang/rubydung/level/Tile.h"
#include "com_mojang/rubydung/level/Tessellator.h"

/* Implement tile rendering to add cube geometry to tessellator */
void Tile_render_grass(Tessellator* t, Level* level, int layer, int x, int y, int z) {
    (void)level; (void)layer;
    tessellator_add_cube(t, (float)x, (float)y, (float)z);
}

void Tile_render_rock(Tessellator* t, Level* level, int layer, int x, int y, int z) {
    (void)level; (void)layer;
    tessellator_add_cube(t, (float)x, (float)y, (float)z);
}
