#include "scrap.h"

#include "math/lxmath.h"

#include <stdio.h>

#define ROTATIONAL_SPEED GetFrameTime ()

Scrap* CreateScrap (Vector2 position) {
    Scrap* scrap = (Scrap*)MemAlloc (sizeof (Scrap));

    scrap->active = 1;
    scrap->position = position;
    scrap->rotation = GetRandomValue (0, 360);
    scrap->rotation_speed = (float)GetRandomValue (-10, 10);

    return scrap;
}

void UpdateScrap (Scrap* scrap) {
    scrap->rotation += ROTATIONAL_SPEED * scrap->rotation_speed;
}

void DestroyScrap (Scrap* scrap) {
    MemFree (scrap);
}

Scrap* FindClosestScrap (Vector2 position, Scrap** scrap_list, int scrap_count) {
    int closest_scrap = 0;
    float distance = 0.0f;

    float closest_distance = Vector2Distance (position, scrap_list[closest_scrap]->position);

    // Should skip first check
    for (int i = 1; i < scrap_count; i++) {
        if (scrap_list[i]->active != 1) continue;

        distance = Vector2Distance (position, scrap_list[i]->position);

        if (distance < closest_distance) {
            closest_distance = distance;
            closest_scrap = i;
        }
    }

    return scrap_list[closest_scrap];
}
