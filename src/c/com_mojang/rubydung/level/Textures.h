#ifndef TEXTURES_H
#define TEXTURES_H

#ifdef __cplusplus
extern "C" {
#endif

int Textures_loadTexture(const char* path, int filter);
void Textures_init(void);

#ifdef __cplusplus
}
#endif

#endif // TEXTURES_H
