#ifndef PLAYER_H
#define PLAYER_H

#include "com_mojang/rubydung/level/Level.h"
#include "com_mojang/rubydung/phys/AABB.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Player {
    Level* level;
    double x, y, z;
    double prevX, prevY, prevZ;
    double motionX, motionY, motionZ;
    float xRotation, yRotation;
    int onGround;
    AABB* boundingBox;
} Player;

Player* Player_new(Level* level);
void Player_turn(Player* p, float dx, float dy);
void Player_tick(Player* p);
void Player_free(Player* p);

#ifdef __cplusplus
}
#endif

#endif // PLAYER_H
