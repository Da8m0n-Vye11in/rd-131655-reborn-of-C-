#include "com_mojang/rubydung/level/Tile.h"
#include <glad/glad.h>
#include <stdio.h>

void Tile_render_grass(Tessellator* t, Level* level, int layer, int x, int y, int z) {
    (void)t; (void)level; (void)layer; (void)x; (void)y; (void)z;
    /* Simple debug: draw a colored cube using immediate mode (compatibility profile) is not available in core.
       For simplicity, we skip actual geometry in this PoC. */
}

void Tile_render_rock(Tessellator* t, Level* level, int layer, int x, int y, int z) {
    (void)t; (void)level; (void)layer; (void)x; (void)y; (void)z;
}
