
#include "global.hpp"
#include "player.hpp"


// --------------raytmx defines
#define RAYTMX_IMPLEMENTATION
#include <raytmx.h>

#define CHECK_COLLISION OBJECT_GROUP true
#define COLLISION_OBJECT_GROUP_NAME "water"
#define SPAWN_COLLISION_OBJECT_GROUP "merchant_start"





#define BASE_WIDTH 960
#define BASE_HEIGHT 540
#define PROJECT_NAME "merchantandthefrog"

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
    #define GLSL_VERSION (100)
#else
    #define GLSL_VERSION (330)
#endif



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
TmxObjectGroup collisionObjectGroup = {};


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
    player = Player(playerSprite, {0,48});
    map = LoadTMX(tmx);
    


    // Camera ---------------------------------------------------------
    camera = { 0 };
    camera.target = {(float)(map->width * map->tileWidth) /2.f , (float)(map->height * map->tileHeight) /2.f};  // Set the camera target to the player
    camera.offset = { BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f };  // Center the camera
    camera.rotation = 0.0f;
    camera.zoom = 6;  // Set the camera zoom to the SCALE factor

    // ADDING COLLISION WALLS TO GROUP FOR PLAYER
    for (size_t i = 0; i < map->layersLength; i++)
    {
        TmxLayer layer = map->layers[i];
        cout << "populating " << endl;
        if (strcmp(layer.name,COLLISION_OBJECT_GROUP_NAME) == 0 && layer.type == LAYER_TYPE_OBJECT_GROUP)
        {
            cout << "layer name is " << layer.name << endl;
            collisionObjectGroup = layer.exact.objectGroup;
            break;
        }
        if (strcmp(layer.name,SPAWN_COLLISION_OBJECT_GROUP) == 0 && layer.type == LAYER_TYPE_OBJECT_GROUP)
        {
            cout << "layer name is " << layer.name << endl;
            player.pos.x = layer.offsetX;
            player.pos.y = layer.offsetY;
            cout << "offset is " << layer.offsetY << endl;
             
        }

    }


}
// ---------------------------------------------------------------------------UPDATE FUNCTION
void Update(void)
{

    player.MovePlayer();

    if (CheckCollisionTMXObjectGroupRec(collisionObjectGroup,player.hitBox,NULL))
    {
        // cout << " inda water" << endl;
    }


}
// ---------------------------------------------------------------------------Draw FUNCTION
void Draw(void)
{

    ClearBackground(BLACK);
    BeginMode2D(camera);
        //DrawTexture(player.sprite,player.pos.x,player.pos.y,WHITE);
        DrawTMX(map,&camera,0,0,WHITE);
        DrawTextureEx(player.sprite,player.pos,0.0,0.5,WHITE);
        DrawRectangleRec(player.hitBox,RED);
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
