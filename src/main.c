#include <raylib.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "scenes/scenes.h"

#define SPACE_PURPLE CLITERAL(Color){  40, 32, 44, 255  }
#define TARGET_FPS 60

// -----------------------------------------------------------------------------
// LOCAL VARIABLES
// -----------------------------------------------------------------------------
static GameScene current_scene;
static GameScene next_scene;

static Texture2D cursor;

// -----------------------------------------------------------------------------
// INLINE HELPER FUNCTIONS
// -----------------------------------------------------------------------------
static inline void InitCurrentScene (void);
static inline void UpdateCurrentScene (void);
static inline void DrawCurrentScene (void);
static inline void GuiDrawCurrentSceneGui (void);
static inline void UnloadCurrentScene (void);

static inline GameScene FinishCurrentScene (void);

// -----------------------------------------------------------------------------
// FUNCTION
// -----------------------------------------------------------------------------
static void UpdateDrawFrame (void);
static void LoadScene (GameScene scene);

int main (int argc, const char* argv[]) {
    const int window_width = 1280;
    const int window_height = 720;

    SetTraceLogLevel (LOG_ERROR);

    InitWindow (window_width, window_height, "Ludum Dare 54");

    HideCursor ();

    #ifdef BUILD_DEBUG
        current_scene = SCENE_WORLD;
    #else
        current_scene = SCENE_MENU;
    #endif

    cursor = LoadTexture ("assets/cursor.png");

    InitCurrentScene ();

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop (UpdateDrawFrame, TARGET_FPS, 1);
    #else
        SetTargetFPS (TARGET_FPS);

        while (!WindowShouldClose ()) {
            UpdateDrawFrame ();
        }
    #endif

    UnloadCurrentScene ();

    UnloadTexture (cursor);

    CloseWindow ();

    return 0;
}

// -----------------------------------------------------------------------------
// FUNCTIONS
// -----------------------------------------------------------------------------
void UpdateDrawFrame (void) {
    UpdateCurrentScene ();

    BeginDrawing ();
        ClearBackground (SPACE_PURPLE);
            DrawCurrentScene ();

            GuiDrawCurrentSceneGui ();

        #ifdef BUILD_DEBUG
            DrawFPS (8, 8);
        #endif

        DrawTextureV (cursor, GetMousePosition (), WHITE);
    EndDrawing ();

    GameScene returned_scene = FinishCurrentScene ();

    if (returned_scene != current_scene) {
        LoadScene (returned_scene);
    }
}

void LoadScene (GameScene scene) {
    UnloadCurrentScene ();

    current_scene = scene;

    InitCurrentScene ();
}

// -----------------------------------------------------------------------------
// INLINE HELPER FUNCTIONS
// -----------------------------------------------------------------------------
void InitCurrentScene (void) {
    switch (current_scene) {
        case SCENE_MENU:    InitMenu (); break;
        case SCENE_WORLD:   InitWorld (); break;
    }
}

void UpdateCurrentScene (void) {
    switch (current_scene) {
        case SCENE_MENU:    UpdateMenu (); break;
        case SCENE_WORLD:   UpdateWorld (); break;
    }
}

void DrawCurrentScene (void) {
    switch (current_scene) {
        case SCENE_MENU:    DrawMenu (); break;
        case SCENE_WORLD:   DrawWorld (); break;
    }
}

void GuiDrawCurrentSceneGui (void) {
    switch (current_scene) {
        case SCENE_MENU:    DrawMenuGui (); break;
        case SCENE_WORLD:   DrawWorldGui (); break;
    }
}

void UnloadCurrentScene (void) {
    switch (current_scene) {
        case SCENE_MENU:    UnloadMenu (); break;
        case SCENE_WORLD:   UnloadWorld (); break;
    }
}

GameScene FinishCurrentScene (void) {
    switch (current_scene) {
        case SCENE_MENU:    return FinishMenu ();
        case SCENE_WORLD:   return FinishWorld ();
    }
}
