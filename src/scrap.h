#ifndef SCRAP_H
#define SCRAP_H

#include <raylib.h>

typedef struct Scrap {
    Vector2 position;

    // Stored as RAD
    float rotation;
    float rotation_speed;

    int active;
} Scrap;

#ifdef __cplusplus
extern "C" {
#endif

Scrap* CreateScrap (Vector2 position);
void UpdateScrap (Scrap* scrap);
void DestroyScrap (Scrap* scrap);

Scrap* FindClosestScrap (Vector2 position, Scrap** scrap_list, int scrap_count);

#ifdef __cplusplus
}
#endif


#endif // SCRAP_H
