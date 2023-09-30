#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef struct Player {
    Texture2D texture;

    Vector2 position;

    // Stored as RAD
    float rotation;
} Player;

#ifdef __cplusplus
extern "C" {
#endif

Player* CreatePlayer ();

#ifdef __cplusplus
}
#endif


#endif // PLAYER_H
