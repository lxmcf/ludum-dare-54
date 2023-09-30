#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define PLAYER_ROTATE_SPEED 5.0f

typedef struct Player {
    Texture2D texture;
    Vector2 texture_origin;
    Rectangle texture_rectangle;

    Vector2 position;

    // Stored as RAD
    float rotation;
} Player;

#ifdef __cplusplus
extern "C" {
#endif

Player* CreatePlayer (Vector2 position);

void UpdatePlayer (Player* player, Camera2D camera);
void DrawPlayer (Player* player);

void UnloadPlayer (Player* player);

#ifdef __cplusplus
}
#endif


#endif // PLAYER_H
