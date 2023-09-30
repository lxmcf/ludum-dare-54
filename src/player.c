#include "player.h"
#include "math/lxmath.h"

Player* CreatePlayer (Vector2 position) {
    Player* player = (Player*)MemAlloc (sizeof (Player));

    player->texture = LoadTexture ("assets/player.png");

    player->texture_origin = CLITERAL(Vector2){
        .x = player->texture.width / 2,
        .y = player->texture.height / 2
    };

    player->texture_rectangle = CLITERAL(Rectangle) {
        .x = 0,
        .y = 0,
        .width = player->texture.width,
        .height = player->texture.height
    };

    player->position = position;
    player->rotation = 0.0f;

    return player;
}

void UpdatePlayer (Player* player, Camera2D camera) {
    float direction = Vector2Angle (player->position, GetScreenToWorld2D (GetMousePosition (), camera));

    player->rotation = SmoothLerp (player->rotation, direction, PLAYER_ROTATE_SPEED * GetFrameTime ());

    #define PLAYER_SPEED 250.0f

    if (IsMouseButtonDown (MOUSE_BUTTON_LEFT)) {
        Vector2 velocity = LengthDirection (PLAYER_SPEED * GetFrameTime (), player->rotation);

        player->position = Vector2Add (player->position, velocity);
    }
}

void DrawPlayer (Player* player) {
    Rectangle destination = CLITERAL(Rectangle){ player->position.x, player->position.y, player->texture.width, player->texture.height };

    DrawTexturePro (player->texture, player->texture_rectangle, destination, player->texture_origin, player->rotation * RAD2DEG, WHITE);
}

void UnloadPlayer (Player* player) {
    UnloadTexture (player->texture);

    MemFree (player);
}
