#include <raylib.h>
#include <stdio.h>

#include "common.h"
#include "math/lxmath.h"
#include "player.h"

static Player* player_ship;

// TEST
static Texture2D background_stars;
static Camera2D camera;

#define WINDOW_CENTRE (Vector2){ window_width / 2, window_height / 2 }

static void DrawTextureTiled (Texture2D texture, Vector2 offset, Color colour);

int main (int argc, const char* argv[]) {
    const int window_width = 1280;
    const int window_height = 720;

    SetTargetFPS (60);

    InitWindow (window_width, window_height, "Ludum Dare 54");

    player_ship = CreatePlayer (WINDOW_CENTRE);

    background_stars = LoadTexture ("assets/background.png");

    camera = CLITERAL(Camera2D){ 0 };
    camera.offset = WINDOW_CENTRE;
    camera.zoom = 1.0f;

    while (!WindowShouldClose ()) {
        UpdatePlayer (player_ship, camera);

        camera.target = player_ship->position;

        BeginDrawing ();
            ClearBackground (RAYWHITE);

            DrawTextureTiled (background_stars, player_ship->position, WHITE);

            BeginMode2D (camera);
                DrawPlayer (player_ship);
            EndMode2D ();

            // DrawFPS (8, 8);
        EndDrawing ();
    }

    UnloadPlayer (player_ship);

    UnloadTexture (background_stars);

    CloseWindow ();

    return 0;
}

void DrawTextureTiled (Texture2D texture, Vector2 offset, Color colour) {
    // CAP WITHIN TEXTURE BOUNDS
    Vector2 adjusted_offset = CLITERAL(Vector2){
        .x = (int)offset.x % texture.width,
        .y = (int)offset.y % texture.height
    };

    for (int x = -texture.width; x < GetScreenWidth () + texture.width; x += texture.width) {
        for (int y = -texture.height; y < GetScreenHeight () + texture.height; y += texture.height) {
            Vector2 position = CLITERAL(Vector2){ .x = x, .y = y };

            DrawTextureV (texture, Vector2Subtract (position, adjusted_offset), colour);
        }
    }
}
