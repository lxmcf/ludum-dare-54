#include "../player.h"
#include "../scrap.h"
#include "../draw.h"
#include "scenes.h"
#include "../math/lxmath.h"
#include "../util/util.h"

static GameScene next_scene;

// -----------------------------------------------------------------------------
// PLAYER VARIABLES
// -----------------------------------------------------------------------------
static Player* player_ship;
static Scrap* closest_scrap;

// -----------------------------------------------------------------------------
// WORLD VARIABLES
// -----------------------------------------------------------------------------
#define SCRAP_COUNT 4
static Scrap* scrap[SCRAP_COUNT];

static Camera2D camera;

// -----------------------------------------------------------------------------
// TEXTURES
// -----------------------------------------------------------------------------
static Texture2D background_layer_1;
static Texture2D background_layer_2;
static Texture2D background_layer_3;

static Texture2D scrap_texture;
static Texture2D ui_arrow;

void InitWorld (void) {
    next_scene = SCENE_WORLD;

    // Player
    player_ship = CreatePlayer (Vector2Zero ());

    // TEXTURES
    background_layer_1 = LoadTexture ("assets/background/stars_1.png");
    background_layer_2 = LoadTexture ("assets/background/stars_2.png");
    background_layer_3 = LoadTexture ("assets/background/stars_3.png");

    scrap_texture = LoadTexture ("assets/test_rubble.png");

    ui_arrow = LoadTexture ("assets/pointer.png");

    // WORLD
    camera = CLITERAL(Camera2D){ 0 };
    camera.offset = CLITERAL(Vector2){ GetScreenWidth () / 2, GetScreenHeight () / 2 };
    camera.zoom = 1.0f;

    for (int i = 0; i < SCRAP_COUNT; i++) {
        scrap[i] = CreateScrap (Vector2MultiplyValue (CLITERAL(Vector2){ 192, 192 }, i));
    }
}

void UpdateWorld (void) {
    UpdatePlayer (player_ship, camera);

    camera.target = player_ship->position;

    for (int i = 0; i < SCRAP_COUNT; i++) {
        UpdateScrap (scrap[i]);
    }

    closest_scrap = FindClosestScrap (player_ship->position, scrap, SCRAP_COUNT);

    if (IsKeyPressed (KEY_SPACE)) {
        next_scene = SCENE_MENU;
    }
}

void DrawWorld (void) {
    DrawTextureTiled (background_layer_1, Vector2MultiplyValue (player_ship->position, 0.25f), WHITE);
    DrawTextureTiled (background_layer_2, Vector2MultiplyValue (player_ship->position, 0.5f), WHITE);
    DrawTextureTiled (background_layer_3, Vector2MultiplyValue (player_ship->position, 0.75f), WHITE);

    BeginMode2D (camera);
        Rectangle output = { 0 };

        for (int i = 0; i < SCRAP_COUNT; i++) {
            output = CLITERAL(Rectangle){
                .x = scrap[i]->position.x,
                .y = scrap[i]->position.y,

                .width = scrap_texture.width,
                .height = scrap_texture.height
            };

            DrawTexturePro (scrap_texture, GetTextureBounds (scrap_texture), output, GetTextureCentre (scrap_texture), scrap[i]->rotation, WHITE);
        }

        float direction = Vector2Angle (player_ship->position, closest_scrap->position);

        output = CLITERAL(Rectangle){
            .x = player_ship->position.x + LengthDirectionX (128, direction),
            .y = player_ship->position.y + LengthDirectionY (128, direction),

            .width = ui_arrow.width,
            .height = ui_arrow.height
        };

        DrawTexturePro (ui_arrow, GetTextureBounds (ui_arrow), output, GetTextureCentre (ui_arrow), direction * RAD2DEG, WHITE);

        DrawPlayer (player_ship);
    EndMode2D ();
}

void DrawWorldGui (void) {

}

void UnloadWorld (void) {
    UnloadPlayer (player_ship);

    UnloadTexture (background_layer_1);
    UnloadTexture (background_layer_2);
    UnloadTexture (background_layer_3);

    UnloadTexture (scrap_texture);

    UnloadTexture (ui_arrow);

    for (int i = 0; i < SCRAP_COUNT; i++) {
        DestroyScrap (scrap[i]);
    }
}

GameScene FinishWorld (void) {
    return next_scene;
}
