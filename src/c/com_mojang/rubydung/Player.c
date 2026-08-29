#include "com_mojang/rubydung/Player.h"
#include <stdlib.h>

Player* Player_new(Level* level) {
    Player* p = (Player*)malloc(sizeof(Player));
    if (!p) return NULL;
    p->level = level;
    p->x = p->y = p->z = 0.0;
    p->prevX = p->prevY = p->prevZ = 0.0;
    p->xRotation = p->yRotation = 0.0f;
    return p;
}

void Player_tick(Player* p) { (void)p; }
void Player_free(Player* p) { if (p) free(p); }
