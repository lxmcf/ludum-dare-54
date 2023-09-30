#include <raylib.h>

#include "common.h"
#include "math/lxmath.h"

#define PLAYER_ROTATE_SPEED 200.0f

static Texture2D background_stars;
static Texture2D player_ship;

#define WINDOW_CENTRE (Vector2){ window_width / 2, window_height / 2 }

int main (int argc, const char* argv[]) {
    const int window_width = 640;
    const int window_height = 360;

    InitWindow (window_width, window_height, "Ludum Dare 54");

    background_stars = LoadTexture ("assets/background.png");
    player_ship = LoadTexture ("assets/player.png");

    float rotation = 0.0f;

    Rectangle source = CLITERAL(Rectangle){ 0, 0, player_ship.width, player_ship.height };
    Rectangle destination = CLITERAL(Rectangle){ window_width / 2, window_height / 2, player_ship.width, player_ship.height };
    Vector2 origin = CLITERAL(Vector2){ player_ship.width / 2, player_ship.height / 2 };

    while (!WindowShouldClose ()) {
        float direction = Vector2Angle (WINDOW_CENTRE, GetMousePosition ());

        rotation = SmoothLerp (rotation, direction, PLAYER_ROTATE_SPEED * DELTA);

        BeginDrawing ();
            ClearBackground (RAYWHITE);

            DrawTexturePro (player_ship, source, destination, origin, rotation * RAD2DEG, WHITE);
            DrawLineV (WINDOW_CENTRE, Vector2Add (WINDOW_CENTRE, LengthDirection (128, direction)), RED);

            // DrawFPS (8, 8);
        EndDrawing ();
    }

    UnloadTexture (background_stars);
    UnloadTexture (player_ship);

    CloseWindow ();

    return 0;
}
