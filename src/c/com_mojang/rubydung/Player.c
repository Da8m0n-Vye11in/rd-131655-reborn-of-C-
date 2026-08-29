#include "com_mojang/rubydung/Player.h"
#include "com_mojang/rubydung/level/Level.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void Player_setPosition(Player* p, float x, float y, float z) {
    p->x = x; p->y = y; p->z = z;
    float width = 0.3f;
    float height = 0.9f;
    if (p->boundingBox) free(p->boundingBox);
    p->boundingBox = AABB_new(x - width, y - height, z - width, x + width, y + height, z + width);
}

static void Player_resetPosition(Player* p) {
    float x = ((float)rand() / (float)RAND_MAX) * p->level->width;
    float y = (float)(p->level->depth + 3);
    float z = ((float)rand() / (float)RAND_MAX) * p->level->height;
    Player_setPosition(p, x, y, z);
}

Player* Player_new(Level* level) {
    Player* p = (Player*)malloc(sizeof(Player));
    if (!p) return NULL;
    p->level = level;
    p->x = p->y = p->z = 0.0;
    p->prevX = p->prevY = p->prevZ = 0.0;
    p->motionX = p->motionY = p->motionZ = 0.0;
    p->xRotation = p->yRotation = 0.0f;
    p->onGround = 0;
    p->boundingBox = NULL;
    Player_resetPosition(p);
    return p;
}

void Player_turn(Player* p, float dx, float dy) {
    if (!p) return;
    p->yRotation += dx * 0.15f;
    p->xRotation -= dy * 0.15f;
    if (p->xRotation > 90.0f) p->xRotation = 90.0f;
    if (p->xRotation < -90.0f) p->xRotation = -90.0f;
}

static void moveRelative(Player* p, float x, float z, float speed) {
    float distance = x * x + z * z;
    if (distance < 0.01f) return;
    distance = speed / sqrtf(distance);
    x *= distance; z *= distance;
    double sinr = sin(p->yRotation * (3.1415926535/180.0));
    double cosr = cos(p->yRotation * (3.1415926535/180.0));
    p->motionX += x * cosr - z * sinr;
    p->motionZ += z * cosr + x * sinr;
}

static float clipY_with_list(AABB** list, int count, AABB* bbox, float y) {
    for (int i=0;i<count;i++) {
        y = AABB_clipYCollide(list[i], bbox, y);
    }
    return y;
}

static float clipX_with_list(AABB** list, int count, AABB* bbox, float x) {
    for (int i=0;i<count;i++) {
        x = AABB_clipXCollide(list[i], bbox, x);
    }
    return x;
}

static float clipZ_with_list(AABB** list, int count, AABB* bbox, float z) {
    for (int i=0;i<count;i++) {
        z = AABB_clipZCollide(list[i], bbox, z);
    }
    return z;
}

void Player_tick(Player* p) {
    if (!p) return;
    p->prevX = p->x; p->prevY = p->y; p->prevZ = p->z;

    float forward = 0.0f; float vertical = 0.0f;

    if (glfwGetKey(NULL, GLFW_KEY_R) == GLFW_PRESS) { /* GLFW requires window pointer; handled by Camera input for reset externally */
        Player_resetPosition(p);
    }

    GLFWwindow* win = glfwGetCurrentContext();
    if (!win) win = NULL;
    if (win) {
        if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) forward--;
        if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) forward++;
        if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) vertical--;
        if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) vertical++;
        if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (p->onGround) p->motionY = 0.12;
        }
    }

    moveRelative(p, vertical, forward, p->onGround ? 0.02f : 0.005f);

    p->motionY -= 0.005;

    /* Move with collision */
    float xa = (float)p->motionX;
    float ya = (float)p->motionY;
    float za = (float)p->motionZ;

    /* gather nearby blocks */
    AABB* expanded = AABB_expand(p->boundingBox, xa, ya, za);
    int count = 0;
    AABB** list = Level_getCubes(p->level, expanded, &count);
    free(expanded);

    /* Y collision */
    float prevYa = ya;
    ya = clipY_with_list(list, count, p->boundingBox, ya);
    AABB_move(p->boundingBox, 0.0f, ya, 0.0f);

    /* X collision */
    float prevXa = xa;
    xa = clipX_with_list(list, count, p->boundingBox, xa);
    AABB_move(p->boundingBox, xa, 0.0f, 0.0f);

    /* Z collision */
    float prevZa = za;
    za = clipZ_with_list(list, count, p->boundingBox, za);
    AABB_move(p->boundingBox, 0.0f, 0.0f, za);

    p->onGround = (prevYa != ya && prevYa < 0.0f) ? 1 : 0;
    if (prevXa != xa) p->motionX = 0.0;
    if (prevYa != ya) p->motionY = 0.0;
    if (prevZa != za) p->motionZ = 0.0;

    p->x = (p->boundingBox->minX + p->boundingBox->maxX) / 2.0;
    p->y = p->boundingBox->minY + 1.62;
    p->z = (p->boundingBox->minZ + p->boundingBox->maxZ) / 2.0;

    /* free list */
    if (list) {
        for (int i=0;i<count;i++) free(list[i]);
        free(list);
    }
}

void Player_free(Player* p) {
    if (!p) return;
    if (p->boundingBox) free(p->boundingBox);
    free(p);
}
