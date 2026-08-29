#ifndef TESSELLATOR_H
#define TESSELLATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tessellator {
    int dummy;
} Tessellator;

void tessellator_init(Tessellator* t);
void tessellator_flush(Tessellator* t);

#ifdef __cplusplus
}
#endif

#endif // TESSELLATOR_H
