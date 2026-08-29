#ifndef PLAYER_H
#define PLAYER_H

#include "com_mojang/rubydung/level/Level.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Player {
    Level* level;
    double x, y, z;
    double prevX, prevY, prevZ;
    float xRotation, yRotation;
} Player;

Player* Player_new(Level* level);
void Player_tick(Player* p);
void Player_free(Player* p);

#ifdef __cplusplus
}
#endif

#endif // PLAYER_H
