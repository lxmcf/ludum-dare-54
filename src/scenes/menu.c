#include <raylib.h>

#include "../math/lxmath.h"
#include "../draw.h"
#include "scenes.h"

#define FONT_SIZE 80
static Font menu_font;

static GameScene next_scene;

// -----------------------------------------------------------------------------
// MENU VARIABLES
// -----------------------------------------------------------------------------
#define BACKGROUND_MOVE_SPEED 100.0f
Vector2 background_offset;

// -----------------------------------------------------------------------------
// TEXTURES
//
// Probably should make something a bit nicer... but duplicates will do!
// -----------------------------------------------------------------------------
static Texture2D background_layer_1;
static Texture2D background_layer_2;
static Texture2D background_layer_3;

void InitMenu (void) {
    menu_font = LoadFontEx ("assets/kenney_space.ttf", FONT_SIZE, 0, 255);

    next_scene = SCENE_MENU;

    // MENU VARIABLES
    background_offset = Vector2Zero ();

    // TEXTURES
    background_layer_1 = LoadTexture ("assets/background/stars_1.png");
    background_layer_2 = LoadTexture ("assets/background/stars_2.png");
    background_layer_3 = LoadTexture ("assets/background/stars_3.png");
}

void UpdateMenu (void) {
    if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
        next_scene = SCENE_WORLD;
    }

    background_offset = Vector2AddValue (background_offset, BACKGROUND_MOVE_SPEED * GetFrameTime ());
}

void DrawMenu (void) {
    DrawTextureTiled (background_layer_1, Vector2MultiplyValue (background_offset, 0.25f), WHITE);
    DrawTextureTiled (background_layer_2, Vector2MultiplyValue (background_offset, 0.5f), WHITE);
    DrawTextureTiled (background_layer_3, Vector2MultiplyValue (background_offset, 0.75f), WHITE);

    DrawTextEx (menu_font, "HELLO WORLD", CLITERAL(Vector2){ 32, 32 }, FONT_SIZE, 1, WHITE);
}

void DrawMenuGui (void) {

}

void UnloadMenu (void) {
    UnloadFont (menu_font);

    UnloadTexture (background_layer_1);
    UnloadTexture (background_layer_2);
    UnloadTexture (background_layer_3);
}

GameScene FinishMenu (void) {
    return next_scene;
}
