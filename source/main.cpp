
#include "global.hpp"
#include "player.hpp"

#define RAYTMX_IMPLEMENTATION
#include "raytmx.h"


#define BASE_WIDTH 960
#define BASE_HEIGHT 540
#define PROJECT_NAME "merchantandthefrog"

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
    #define GLSL_VERSION (100)
#else
    #define GLSL_VERSION (330)
#endif

static int screen_width, screen_height, screen_scale;

void Init(void);
void Update(void);
void Draw(void);
void Unload(void);
void UpdateDrawFrame(void);


// ---------- global classes
Player player;

// -------- textures

Texture2D playerSprite;
TmxMap* map;


// ---------- global vars

Camera2D camera;


// ---------------------------------------------------------------------------MAIN FUNCTION
int main(void)
{
    Init();



#ifdef PLATFORM_WEB
    // (main loop function, fps, simulate infinite loop)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
    Unload();
    return 0;
}
// ---------------------------------------------------------------------------INIT FUNCTION
void Init(void)
{
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(BASE_WIDTH, BASE_HEIGHT, PROJECT_NAME);

    SetWindowMinSize(BASE_WIDTH, BASE_HEIGHT);

    SetTargetFPS(60);

    const char* tmx = "maps/frog-level1.tmx";

    // ---------load textures and maps 
    playerSprite = LoadTexture("assets/player.png");

    // ---------load objects
    player = Player(playerSprite, {0,0});
    map = LoadTMX(tmx);
    


    // Camera ---------------------------------------------------------
    camera = { 0 };
    camera.target = {(float)(map->width * map->tileWidth) /2.f , (float)(map->height * map->tileHeight) /2.f};  // Set the camera target to the player
    camera.offset = { screen_width / 2.0f, screen_height / 2.0f };  // Center the camera
    camera.rotation = 0.0f;
    camera.zoom = 2;  // Set the camera zoom to the SCALE factor

}
// ---------------------------------------------------------------------------UPDATE FUNCTION
void Update(void)
{

    player.MovePlayer();

}
// ---------------------------------------------------------------------------Draw FUNCTION
void Draw(void)
{

    ClearBackground(BLACK);
    BeginMode2D(camera);
        //DrawTexture(player.sprite,player.pos.x,player.pos.y,WHITE);
        DrawTMX(map,&camera,0,0,WHITE);
        DrawTextureEx(player.sprite,player.pos,0.0,0.5,WHITE);
    EndMode2D();

}
// ---------------------------------------------------------------------------UNLOAD FUNCTION
void Unload(void)
{

#ifdef PLATFORM_WEB
    emscripten_exit_with_live_runtime();
#endif
    CloseWindow();
}
// ---------------------------------------------------------------------------UPDATE AND DRAW FUNCTION
void UpdateDrawFrame(void)
{
    Update();

    BeginDrawing();
        Draw();
    EndDrawing();
}
