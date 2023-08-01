#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "array.h"
#include "button.h"
#include "sprite.h"
#include "scene.h"
#include "game_data.h"

#include "scene_0000.h"



enum scene_transision_enum
{
    SCENE_TRANSITION_IDLE,
    SCENE_TRANSITION_START,
    SCENE_TRANSITION_FADE_OUT,
    SCENE_TRANSITION_RUN,
    SCENE_TRANSITION_WAIT,
    SCENE_TRANSITION_FADE_IN,
    SCENE_TRANSITION_END
};



bool exit_window;

struct game_data game_data;

float elapsed_time;

bool is_mouse_input_enabled;
bool is_draw_mouse;

Texture2D mouse_cursor_textures[5];
Vector2 mouse_cursor_offsets[5];

int current_mouse_cursor_index;

int current_scene_index;
int next_scene_index;

bool is_scene_transition;
enum scene_transision_enum scene_transition_state;
float scene_transition_fade_out_time;
float scene_transition_wait_time;
float scene_transition_fade_in_time;
float scene_transition_timer;
Color scene_transition_color;

bool is_draw_debug;

struct scene scene;

struct array function_pointers_scene_init;
struct array function_pointers_scene_free;
struct array function_pointers_scene_enter;
struct array function_pointers_scene_exit;
struct array function_pointers_scene_update;
struct array function_pointers_scene_draw;

RenderTexture2D render_texture;

struct button * current_button;



void game_init(void);
void game_free(void);
void game_reset(void);

void game_update(float delta);
void game_update_scene_transition(float delta);
void game_update_scene(float delta);

void game_draw(void);
void game_draw_scene(void);
void game_draw_mouse(void);
void game_draw_scene_transition(void);
void game_draw_debug(void);
void game_draw_render_texture(void);



void add_scene(void(*scene_init)(void), void(*scene_free)(void), void(*scene_enter)(void), void(*scene_exit)(void), void(*scene_update)(float delta), void(*scene_draw)(void));
void set_scene(int index);

void add_button(int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index,
    void(*on_pressed)(void), void(*on_down)(void), void(*on_released)(void));

void add_sprite(int x, int y, char * texture_filename, Color tint, bool is_visible);



/* -------- scene_title -------- */

struct sprite * scene_title_sprite_background;

struct sprite * scene_title_sprite_new_game_over;
struct sprite * scene_title_sprite_load_game_over;
struct sprite * scene_title_sprite_quit_over;
struct sprite * scene_title_sprite_options_over;

struct button * scene_title_button_new_game;
struct button * scene_title_button_load_game;
struct button * scene_title_button_quit;
struct button * scene_title_button_options;

void scene_title_init(void);
void scene_title_free(void);

void scene_title_enter(void);
void scene_title_exit(void);

void scene_title_update(float delta);
void scene_title_draw(void);

void scene_title_on_released_button_new_game(void);
void scene_title_on_released_button_load_game(void);
void scene_title_on_released_button_quit(void);
void scene_title_on_released_button_options(void);

/* -------- scene_title -------- */



/* -------- scene_credits -------- */

struct sprite * scene_credits_sprite_slide_0000;
struct sprite * scene_credits_sprite_slide_0001;
struct sprite * scene_credits_sprite_slide_0002;
struct sprite * scene_credits_sprite_slide_0003;
struct sprite * scene_credits_sprite_slide_0004;
struct sprite * scene_credits_sprite_slide_0005;
struct sprite * scene_credits_sprite_slide_0006;

struct button * scene_credits_button_quit;

float scene_credits_slide_time;
float scene_credits_slide_timer;

size_t scene_credits_slides_count;
struct sprite * scene_credits_slides[7];

size_t scene_credits_current_slide_index;

void scene_credits_init(void);
void scene_credits_free(void);

void scene_credits_enter(void);
void scene_credits_exit(void);

void scene_credits_update(float delta);
void scene_credits_draw(void);

void scene_credits_on_released_button_quit(void);

/* -------- scene_credits -------- */



/* -------- scene_0000 -------- */

struct sprite * scene_0000_sprite_background;

struct button * scene_0000_button_exit;

void scene_0000_init(void);
void scene_0000_free(void);

void scene_0000_enter(void);
void scene_0000_exit(void);

void scene_0000_update(float delta);
void scene_0000_draw(void);

void scene_0000_on_released_button_exit(void);

/* -------- scene_0000 -------- */



/* -------- scene_0001 -------- */

struct sprite * scene_0001_sprite_background;

struct button * scene_0001_button_exit_0;
struct button * scene_0001_button_exit_1;
struct button * scene_0001_button_exit_2;

void scene_0001_init(void);
void scene_0001_free(void);

void scene_0001_enter(void);
void scene_0001_exit(void);

void scene_0001_update(float delta);
void scene_0001_draw(void);

void scene_0001_on_released_button_exit_0(void);

void scene_0001_on_released_button_exit_1(void);

void scene_0001_on_released_button_exit_2(void);

/* -------- scene_0001 -------- */



/* -------- scene_0002 -------- */

struct sprite * scene_0002_sprite_background;

struct button * scene_0002_button_exit_0;
struct button * scene_0002_button_exit_1;

void scene_0002_init(void);
void scene_0002_free(void);

void scene_0002_enter(void);
void scene_0002_exit(void);

void scene_0002_update(float delta);
void scene_0002_draw(void);

void scene_0002_on_released_button_exit_0(void);

void scene_0002_on_released_button_exit_1(void);

/* -------- scene_0002 -------- */



/* -------- scene_0003 -------- */

struct sprite * scene_0003_sprite_background;

struct button * scene_0003_button_exit_0;
struct button * scene_0003_button_exit_1;

void scene_0003_init(void);
void scene_0003_free(void);

void scene_0003_enter(void);
void scene_0003_exit(void);

void scene_0003_update(float delta);
void scene_0003_draw(void);

void scene_0003_on_released_button_exit_0(void);

void scene_0003_on_released_button_exit_1(void);

/* -------- scene_0003 -------- */



/* -------- scene_0004 -------- */

struct sprite * scene_0004_sprite_background;

struct button * scene_0004_button_exit_0;
struct button * scene_0004_button_exit_1;

void scene_0004_init(void);
void scene_0004_free(void);

void scene_0004_enter(void);
void scene_0004_exit(void);

void scene_0004_update(float delta);
void scene_0004_draw(void);

void scene_0004_on_released_button_exit_0(void);

void scene_0004_on_released_button_exit_1(void);

/* -------- scene_0004 -------- */



/* -------- scene_0005 -------- */

struct sprite * scene_0005_sprite_background;
struct sprite * scene_0005_sprite_lever_down;
struct sprite * scene_0005_sprite_lever_up;

struct button * scene_0005_button_lever;
struct button * scene_0005_button_exit_0;
struct button * scene_0005_button_exit_1;

Sound scene_0005_sound_lever;

bool scene_0005_is_lever_down;

void scene_0005_init(void);
void scene_0005_free(void);

void scene_0005_enter(void);
void scene_0005_exit(void);

void scene_0005_update(float delta);
void scene_0005_draw(void);

void scene_0005_on_released_button_lever(void);

void scene_0005_on_released_button_exit_0(void);

void scene_0005_on_released_button_exit_1(void);

/* -------- scene_0005 -------- */



/* -------- scene_0006 -------- */

struct sprite * scene_0006_sprite_background;

struct button * scene_0006_button_exit_0;
struct button * scene_0006_button_exit_1;
struct button * scene_0006_button_exit_2;

void scene_0006_init(void);
void scene_0006_free(void);

void scene_0006_enter(void);
void scene_0006_exit(void);

void scene_0006_update(float delta);
void scene_0006_draw(void);

void scene_0006_on_released_button_exit_0(void);

void scene_0006_on_released_button_exit_1(void);

void scene_0006_on_released_button_exit_2(void);

/* -------- scene_0006 -------- */



/* -------- scene_0007 -------- */

struct sprite * scene_0007_sprite_background;

struct button * scene_0007_button_exit_0;
struct button * scene_0007_button_exit_1;

void scene_0007_init(void);
void scene_0007_free(void);

void scene_0007_enter(void);
void scene_0007_exit(void);

void scene_0007_update(float delta);
void scene_0007_draw(void);

void scene_0007_on_released_button_exit_0(void);

void scene_0007_on_released_button_exit_1(void);

/* -------- scene_0007 -------- */



/* -------- scene_0008 -------- */

struct sprite * scene_0008_sprite_background;

struct button * scene_0008_button_exit_0;
struct button * scene_0008_button_exit_1;
struct button * scene_0008_button_exit_2;

void scene_0008_init(void);
void scene_0008_free(void);

void scene_0008_enter(void);
void scene_0008_exit(void);

void scene_0008_update(float delta);
void scene_0008_draw(void);

void scene_0008_on_released_button_exit_0(void);

void scene_0008_on_released_button_exit_1(void);

void scene_0008_on_released_button_exit_2(void);

/* -------- scene_0008 -------- */



/* -------- scene_0009 -------- */

struct sprite * scene_0009_sprite_background;

struct button * scene_0009_button_exit_0;
struct button * scene_0009_button_exit_1;
struct button * scene_0009_button_exit_2;

void scene_0009_init(void);
void scene_0009_free(void);

void scene_0009_enter(void);
void scene_0009_exit(void);

void scene_0009_update(float delta);
void scene_0009_draw(void);

void scene_0009_on_released_button_exit_0(void);

void scene_0009_on_released_button_exit_1(void);

void scene_0009_on_released_button_exit_2(void);

/* -------- scene_0009 -------- */



/* -------- scene_0010 -------- */

struct sprite * scene_0010_sprite_background;

struct button * scene_0010_button_exit_0;
struct button * scene_0010_button_exit_1;
struct button * scene_0010_button_exit_2;
struct button * scene_0010_button_exit_3;

void scene_0010_init(void);
void scene_0010_free(void);

void scene_0010_enter(void);
void scene_0010_exit(void);

void scene_0010_update(float delta);
void scene_0010_draw(void);

void scene_0010_on_released_button_exit_0(void);

void scene_0010_on_released_button_exit_1(void);

void scene_0010_on_released_button_exit_2(void);

void scene_0010_on_released_button_exit_3(void);

/* -------- scene_0010 -------- */



/* -------- scene_0011 -------- */

struct sprite * scene_0011_sprite_background;

struct button * scene_0011_button_exit_0;
struct button * scene_0011_button_exit_1;
struct button * scene_0011_button_exit_2;

void scene_0011_init(void);
void scene_0011_free(void);

void scene_0011_enter(void);
void scene_0011_exit(void);

void scene_0011_update(float delta);
void scene_0011_draw(void);

void scene_0011_on_released_button_exit_0(void);

void scene_0011_on_released_button_exit_1(void);

void scene_0011_on_released_button_exit_2(void);

/* -------- scene_0011 -------- */



/* -------- scene_0012 -------- */

struct sprite * scene_0012_sprite_background;

struct button * scene_0012_button_exit_0;
struct button * scene_0012_button_exit_1;
struct button * scene_0012_button_exit_2;

void scene_0012_init(void);
void scene_0012_free(void);

void scene_0012_enter(void);
void scene_0012_exit(void);

void scene_0012_update(float delta);
void scene_0012_draw(void);

void scene_0012_on_released_button_exit_0(void);

void scene_0012_on_released_button_exit_1(void);

void scene_0012_on_released_button_exit_2(void);

/* -------- scene_0012 -------- */



/* -------- scene_0013 -------- */

struct sprite * scene_0013_sprite_background;

struct button * scene_0013_button_exit_0;
struct button * scene_0013_button_exit_1;
struct button * scene_0013_button_exit_2;

void scene_0013_init(void);
void scene_0013_free(void);

void scene_0013_enter(void);
void scene_0013_exit(void);

void scene_0013_update(float delta);
void scene_0013_draw(void);

void scene_0013_on_released_button_exit_0(void);

void scene_0013_on_released_button_exit_1(void);

void scene_0013_on_released_button_exit_2(void);

/* -------- scene_0013 -------- */



/* -------- scene_0014 -------- */

struct sprite * scene_0014_sprite_background;

struct button * scene_0014_button_exit_0;
struct button * scene_0014_button_exit_1;
struct button * scene_0014_button_exit_2;

void scene_0014_init(void);
void scene_0014_free(void);

void scene_0014_enter(void);
void scene_0014_exit(void);

void scene_0014_update(float delta);
void scene_0014_draw(void);

void scene_0014_on_released_button_exit_0(void);

void scene_0014_on_released_button_exit_1(void);

void scene_0014_on_released_button_exit_2(void);

/* -------- scene_0014 -------- */



/* -------- scene_0015 -------- */

struct sprite * scene_0015_sprite_background;
struct sprite * scene_0015_sprite_lever_down;
struct sprite * scene_0015_sprite_lever_up;

struct button * scene_0015_button_lever;
struct button * scene_0015_button_exit_0;
struct button * scene_0015_button_exit_1;

Sound scene_0015_sound_lever;

bool scene_0015_is_lever_down;

void scene_0015_init(void);
void scene_0015_free(void);

void scene_0015_enter(void);
void scene_0015_exit(void);

void scene_0015_update(float delta);
void scene_0015_draw(void);

void scene_0015_on_released_button_lever(void);

void scene_0015_on_released_button_exit_0(void);

void scene_0015_on_released_button_exit_1(void);

/* -------- scene_0015 -------- */



/* -------- scene_0016 -------- */

struct sprite * scene_0016_sprite_background;

struct button * scene_0016_button_exit_0;
struct button * scene_0016_button_exit_1;
struct button * scene_0016_button_exit_2;

void scene_0016_init(void);
void scene_0016_free(void);

void scene_0016_enter(void);
void scene_0016_exit(void);

void scene_0016_update(float delta);
void scene_0016_draw(void);

void scene_0016_on_released_button_exit_0(void);

void scene_0016_on_released_button_exit_1(void);

void scene_0016_on_released_button_exit_2(void);

/* -------- scene_0016 -------- */



/* -------- scene_0017 -------- */

struct sprite * scene_0017_sprite_background;

struct button * scene_0017_button_exit_0;
struct button * scene_0017_button_exit_1;
struct button * scene_0017_button_exit_2;

void scene_0017_init(void);
void scene_0017_free(void);

void scene_0017_enter(void);
void scene_0017_exit(void);

void scene_0017_update(float delta);
void scene_0017_draw(void);

void scene_0017_on_released_button_exit_0(void);

void scene_0017_on_released_button_exit_1(void);

/* -------- scene_0017 -------- */



int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(544, 332, "Missed");
    InitAudioDevice();
    SetTargetFPS(60);
    HideCursor();

    //Music music = LoadMusicStream("resources/music_0000.ogg");
    //PlayMusicStream(music);

    exit_window = false;

    game_init();

    while (!exit_window)
    {
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) exit_window = true;
        //UpdateMusicStream(music);

        float delta = GetFrameTime();
        game_update(delta);
        game_draw();
    }

    game_free();

    //UnloadMusicStream(music);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}



void game_init(void)
{
    printf("game_init\n");

    game_data = game_data_create();
    game_data_init(&game_data);

    elapsed_time = 0.0f;

    is_mouse_input_enabled = false;
    is_draw_mouse = true;

    mouse_cursor_textures[0] = LoadTexture("resources/mouse_cursor/0000.png");
    mouse_cursor_textures[1] = LoadTexture("resources/mouse_cursor/0001.png");
    mouse_cursor_textures[2] = LoadTexture("resources/mouse_cursor/0002.png");
    mouse_cursor_textures[3] = LoadTexture("resources/mouse_cursor/0003.png");
    mouse_cursor_textures[4] = LoadTexture("resources/mouse_cursor/0004.png");

    mouse_cursor_offsets[0] = (Vector2){ -2.0f, -8.0f };
    mouse_cursor_offsets[1] = (Vector2){ -8.0f, -2.0f };
    mouse_cursor_offsets[2] = (Vector2){ -15.0f, -8.0f };
    mouse_cursor_offsets[3] = (Vector2){ -8.0f, -15.0f };
    mouse_cursor_offsets[4] = (Vector2){ -8.0f, -2.0f };

    current_mouse_cursor_index = 1;

    current_scene_index = -1;
    next_scene_index = 18;

    is_scene_transition = true;
    scene_transition_state = SCENE_TRANSITION_RUN;
    scene_transition_fade_out_time = 0.0f;
    scene_transition_wait_time = 0.0f;
    scene_transition_fade_in_time = 0.0f;
    scene_transition_timer = 0.0f;
    scene_transition_color = BLACK;

    scene = (struct scene){ 0 };

    function_pointers_scene_init = array_create(1, sizeof(void(*)(void)));
    function_pointers_scene_free = array_create(1, sizeof(void(*)(void)));
    function_pointers_scene_enter = array_create(1, sizeof(void(*)(void)));
    function_pointers_scene_exit = array_create(1, sizeof(void(*)(void)));
    function_pointers_scene_update = array_create(1, sizeof(void(*)(float delta)));
    function_pointers_scene_draw = array_create(1, sizeof(void(*)(void)));

    array_init(&function_pointers_scene_init);
    array_init(&function_pointers_scene_free);
    array_init(&function_pointers_scene_enter);
    array_init(&function_pointers_scene_exit);
    array_init(&function_pointers_scene_update);
    array_init(&function_pointers_scene_draw);

    add_scene(scene_title_init, scene_title_free, scene_title_enter, scene_title_exit, scene_title_update, scene_title_draw);
    add_scene(scene_credits_init, scene_credits_free, scene_credits_enter, scene_credits_exit, scene_credits_update, scene_credits_draw);
    add_scene(scene_0000_init, scene_0000_free, scene_0000_enter, scene_0000_exit, scene_0000_update, scene_0000_draw);
    add_scene(scene_0001_init, scene_0001_free, scene_0001_enter, scene_0001_exit, scene_0001_update, scene_0001_draw);
    add_scene(scene_0002_init, scene_0002_free, scene_0002_enter, scene_0002_exit, scene_0002_update, scene_0002_draw);
    add_scene(scene_0003_init, scene_0003_free, scene_0003_enter, scene_0003_exit, scene_0003_update, scene_0003_draw);
    add_scene(scene_0004_init, scene_0004_free, scene_0004_enter, scene_0004_exit, scene_0004_update, scene_0004_draw);
    add_scene(scene_0005_init, scene_0005_free, scene_0005_enter, scene_0005_exit, scene_0005_update, scene_0005_draw);
    add_scene(scene_0006_init, scene_0006_free, scene_0006_enter, scene_0006_exit, scene_0006_update, scene_0006_draw);
    add_scene(scene_0007_init, scene_0007_free, scene_0007_enter, scene_0007_exit, scene_0007_update, scene_0007_draw);
    add_scene(scene_0008_init, scene_0008_free, scene_0008_enter, scene_0008_exit, scene_0008_update, scene_0008_draw);
    add_scene(scene_0009_init, scene_0009_free, scene_0009_enter, scene_0009_exit, scene_0009_update, scene_0009_draw);
    add_scene(scene_0010_init, scene_0010_free, scene_0010_enter, scene_0010_exit, scene_0010_update, scene_0010_draw);
    add_scene(scene_0011_init, scene_0011_free, scene_0011_enter, scene_0011_exit, scene_0011_update, scene_0011_draw);
    add_scene(scene_0012_init, scene_0012_free, scene_0012_enter, scene_0012_exit, scene_0012_update, scene_0012_draw);
    add_scene(scene_0013_init, scene_0013_free, scene_0013_enter, scene_0013_exit, scene_0013_update, scene_0013_draw);
    add_scene(scene_0014_init, scene_0014_free, scene_0014_enter, scene_0014_exit, scene_0014_update, scene_0014_draw);
    add_scene(scene_0015_init, scene_0015_free, scene_0015_enter, scene_0015_exit, scene_0015_update, scene_0015_draw);
    add_scene(scene_0016_init, scene_0016_free, scene_0016_enter, scene_0016_exit, scene_0016_update, scene_0016_draw);
    add_scene(scene_0017_init, scene_0017_free, scene_0017_enter, scene_0017_exit, scene_0017_update, scene_0017_draw);

    is_draw_debug = true;

    render_texture = LoadRenderTexture(544, 332);

    current_button = NULL;
}
void game_free(void)
{
    printf("game_free\n");

    if (current_scene_index != -1)
    {
        (*(void(**)(void))array_get(&function_pointers_scene_exit, current_scene_index))();
        (*(void(**)(void))array_get(&function_pointers_scene_free, current_scene_index))();
        scene_free(&scene);
        scene = (struct scene){ 0 };
    }

    game_data_free(&game_data);
    game_data = (struct game_data){ 0 };

    elapsed_time = 0.0f;

    is_mouse_input_enabled = false;
    is_draw_mouse = false;

    for (int i = 0; i < 4; ++i)
    {
        UnloadTexture(mouse_cursor_textures[i]);
        mouse_cursor_offsets[0] = (Vector2){ 0.0f, 0.0f };
    }

    current_mouse_cursor_index = -1;

    current_scene_index = -1;
    next_scene_index = -1;

    is_scene_transition = false;
    scene_transition_state = SCENE_TRANSITION_IDLE;
    scene_transition_fade_out_time = 0.0f;
    scene_transition_wait_time = 0.0f;
    scene_transition_fade_in_time = 0.0f;
    scene_transition_timer = 0.0f;
    scene_transition_color = BLANK;

    scene = (struct scene){ 0 };

    array_free(&function_pointers_scene_init);
    array_free(&function_pointers_scene_free);
    array_free(&function_pointers_scene_enter);
    array_free(&function_pointers_scene_exit);
    array_free(&function_pointers_scene_update);
    array_free(&function_pointers_scene_draw);

    function_pointers_scene_init = (struct array){ 0 };
    function_pointers_scene_free = (struct array){ 0 };
    function_pointers_scene_enter = (struct array){ 0 };
    function_pointers_scene_exit = (struct array){ 0 };
    function_pointers_scene_update = (struct array){ 0 };
    function_pointers_scene_draw = (struct array){ 0 };

    is_draw_debug = false;

    UnloadRenderTexture(render_texture);

    current_button = NULL;
}
void game_reset(void)
{
    printf("game_reset\n");

    game_free();
    game_init();
}

void game_update(float delta)
{
    elapsed_time += delta;

    if (IsKeyPressed(KEY_R))
    {
        game_reset();
    }
    if (IsKeyPressed(KEY_D))
    {
        is_draw_debug = !is_draw_debug;
    }

    if (is_scene_transition)
    {
        game_update_scene_transition(delta);
    }

    if (current_scene_index != -1)
    {
        game_update_scene(delta);
    }
}
void game_update_scene_transition(float delta)
{
    if (scene_transition_state == SCENE_TRANSITION_START)
    {
        scene_transition_timer = 0.0f;
        scene_transition_color.a = 0;
        scene_transition_state = SCENE_TRANSITION_FADE_OUT;
    }
    if (scene_transition_state == SCENE_TRANSITION_FADE_OUT)
    {
        scene_transition_timer += delta;
        if (scene_transition_timer < scene_transition_fade_out_time)
        {
            scene_transition_color.a = (unsigned char)(255 * (scene_transition_timer / scene_transition_fade_out_time));
        }
        else
        {
            scene_transition_color.a = 255;
            scene_transition_timer = 0.0f;
            scene_transition_state = SCENE_TRANSITION_RUN;
        }
    }
    if (scene_transition_state == SCENE_TRANSITION_RUN)
    {
        if (current_scene_index != -1)
        {
            (*(void(**)(void))array_get(&function_pointers_scene_exit, current_scene_index))();
            (*(void(**)(void))array_get(&function_pointers_scene_free, current_scene_index))();
            scene_free(&scene);
            scene = (struct scene){ 0 };
        }
        current_scene_index = next_scene_index;
        next_scene_index = -1;
        if (current_scene_index != -1)
        {
            scene = scene_create();
            scene_init(&scene);

            (*(void(**)(void))array_get(&function_pointers_scene_init, current_scene_index))();
            (*(void(**)(void))array_get(&function_pointers_scene_enter, current_scene_index))();
        }
        scene_transition_state = SCENE_TRANSITION_WAIT;
    }
    if (scene_transition_state == SCENE_TRANSITION_WAIT)
    {
        scene_transition_timer += delta;
        if (scene_transition_timer >= scene_transition_wait_time)
        {
            scene_transition_timer = 0.0f;
            scene_transition_state = SCENE_TRANSITION_FADE_IN;
        }
    }
    if (scene_transition_state == SCENE_TRANSITION_FADE_IN)
    {
        scene_transition_timer += delta;
        if (scene_transition_timer < scene_transition_fade_in_time)
        {
            scene_transition_color.a = (unsigned char)(255 * (1.0f - (scene_transition_timer / scene_transition_fade_in_time)));
        }
        else
        {
            scene_transition_color.a = 0;
            scene_transition_timer = 0.0f;
            scene_transition_state = SCENE_TRANSITION_END;
        }
    }
    if (scene_transition_state == SCENE_TRANSITION_END)
    {
        is_mouse_input_enabled = true;
        is_scene_transition = false;
        scene_transition_state = SCENE_TRANSITION_IDLE;
    }
}
void game_update_scene(float delta)
{
    scene_translate_elapsed_time(&scene, delta);

    current_mouse_cursor_index = 1;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        struct button * ptr = NULL;

        for (int i = 0; i < scene_get_buttons_count(&scene); ++i)
        {
            struct button * button = scene_get_button(&scene, i);

            if (!button_get_is_enabled(button))
            {
                button_set_was_mouse_over(button, false);
                button_set_is_mouse_over(button, false);
                button_set_was_down(button, false);
                button_set_is_down(button, false);
                continue;
            }

            button_set_was_mouse_over(button, button_get_is_mouse_over(button));
            button_set_is_mouse_over(button, false);

            button_set_was_down(button, button_get_is_down(button));
            button_set_is_down(button, false);

            if (ptr == NULL)
            {
                int x = button_get_x(button);
                int y = button_get_y(button);
                int width = button_get_width(button);
                int height = button_get_height(button);

                if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
                {
                    ptr = button;
                    current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                    button_set_is_mouse_over(button, true);
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (ptr != NULL)
            {
                current_button = ptr;
                button_set_is_down(current_button, true);
                if (button_get_on_pressed(current_button) != NULL) button_get_on_pressed(current_button)();
                if (button_get_on_down(current_button) != NULL) button_get_on_down(current_button)();
            }
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (current_button != NULL && ptr == current_button)
            {
                button_set_is_down(current_button, true);
                if (button_get_on_down(current_button) != NULL) button_get_on_down(current_button)();
            }
            else if (current_button != NULL && ptr != current_button)
            {
                //button_get_on_released(current_button)();
                current_button = NULL;
            }
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (current_button != NULL)
            {
                if (button_get_on_released(current_button) != NULL) button_get_on_released(current_button)();
                current_button = NULL;
            }
        }
    }

    (*(void(**)(float delta))array_get(&function_pointers_scene_update, current_scene_index))(delta);
}

void game_draw(void)
{
    BeginTextureMode(render_texture);

    ClearBackground((Color) { 255, 0, 255, 255 });

    if (current_scene_index != -1)
    {
        game_draw_scene();
    }

    if (is_draw_mouse)
    {
        game_draw_mouse();
    }

    if (is_scene_transition)
    {
        game_draw_scene_transition();
    }

    if (is_draw_debug)
    {
        game_draw_debug();
    }

    EndTextureMode();

    BeginDrawing();

    ClearBackground(BLACK);

    game_draw_render_texture();

    EndDrawing();
}
void game_draw_scene(void)
{
    for (int i = 0; i < scene_get_sprites_count(&scene); ++i)
    {
        struct sprite * sprite = scene_get_sprite(&scene, i);
        sprite_draw(sprite);
    }

    for (int i = 0; i < scene_get_buttons_count(&scene); ++i)
    {
        struct button * button = scene_get_button(&scene, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }

    (*(void(**)(void))array_get(&function_pointers_scene_draw, current_scene_index))();
}
void game_draw_mouse(void)
{
    Vector2 mouse_position = GetMousePosition();
    mouse_position.x += mouse_cursor_offsets[current_mouse_cursor_index].x;
    mouse_position.y += mouse_cursor_offsets[current_mouse_cursor_index].y;
    DrawTexture(mouse_cursor_textures[current_mouse_cursor_index], mouse_position.x, mouse_position.y, WHITE);
}
void game_draw_scene_transition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), scene_transition_color);
}
void game_draw_debug(void)
{
    DrawRectangle(0, 0, 138, 26, BLACK);
    DrawText(TextFormat("current_scene_index: %d", current_scene_index), 8, 8, 8, WHITE);
}
void game_draw_render_texture(void)
{
    Rectangle source = (Rectangle){ 0.0f, 0.0f, (float)render_texture.texture.width, -(float)render_texture.texture.height };
    Rectangle dest = (Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    DrawTexturePro(render_texture.texture, source, dest, (Vector2) { 0.0f, 0.0f }, 0.0f, WHITE);
}



void add_scene(void(*scene_init)(void), void(*scene_free)(void), void(*scene_enter)(void), void(*scene_exit)(void), void(*scene_update)(float delta), void(*scene_draw)(void))
{
    array_append(&function_pointers_scene_init, &scene_init);
    array_append(&function_pointers_scene_free, &scene_free);
    array_append(&function_pointers_scene_enter, &scene_enter);
    array_append(&function_pointers_scene_exit, &scene_exit);
    array_append(&function_pointers_scene_update, &scene_update);
    array_append(&function_pointers_scene_draw, &scene_draw);
}
void set_scene(int index)
{
    printf("set_scene: index=%d\n", index);

    is_mouse_input_enabled = false;
    next_scene_index = index;
    is_scene_transition = true;
    scene_transition_state = SCENE_TRANSITION_START;
}



/* -------- scene_title -------- */

void scene_title_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_title/background.png", WHITE, true);

    scene_add_sprite(&scene, 446, 249, "resources/scene_title/new_game_over.png", WHITE, false);
    scene_add_sprite(&scene, 439, 266, "resources/scene_title/load_game_over.png", WHITE, false);
    scene_add_sprite(&scene, 493, 317, "resources/scene_title/quit_over.png", WHITE, false);
    scene_add_sprite(&scene, 10, 310, "resources/scene_title/options_over.png", WHITE, false);

    scene_add_button(&scene, 446, 249, 87, 12, BLANK, true, 1,
        NULL, NULL, scene_title_on_released_button_new_game);

    scene_add_button(&scene, 439, 266, 94, 12, BLANK, true, 1,
        NULL, NULL, scene_title_on_released_button_load_game);

    scene_add_button(&scene, 493, 317, 41, 13, BLANK, true, 1,
        NULL, NULL, scene_title_on_released_button_quit);

    scene_add_button(&scene, 10, 310, 74, 12, BLANK, true, 1,
        NULL, NULL, scene_title_on_released_button_options);
}
void scene_title_free(void)
{

}

void scene_title_enter(void)
{
    scene_title_sprite_background = scene_get_sprite(&scene, 0);

    scene_title_sprite_new_game_over = scene_get_sprite(&scene, 1);
    scene_title_sprite_load_game_over = scene_get_sprite(&scene, 2);
    scene_title_sprite_quit_over = scene_get_sprite(&scene, 3);
    scene_title_sprite_options_over = scene_get_sprite(&scene, 4);

    scene_title_button_new_game = scene_get_button(&scene, 0);
    scene_title_button_load_game = scene_get_button(&scene, 1);
    scene_title_button_quit = scene_get_button(&scene, 2);
    scene_title_button_options = scene_get_button(&scene, 3);
}
void scene_title_exit(void)
{
    scene_title_sprite_background = NULL;

    scene_title_sprite_new_game_over = NULL;
    scene_title_sprite_load_game_over = NULL;
    scene_title_sprite_quit_over = NULL;
    scene_title_sprite_options_over = NULL;

    scene_title_button_new_game = NULL;
    scene_title_button_load_game = NULL;
    scene_title_button_quit = NULL;
    scene_title_button_options = NULL;
}

void scene_title_update(float delta)
{
    sprite_set_is_visible(scene_title_sprite_new_game_over, button_get_is_mouse_over(scene_title_button_new_game));
    sprite_set_is_visible(scene_title_sprite_load_game_over, button_get_is_mouse_over(scene_title_button_load_game));
    sprite_set_is_visible(scene_title_sprite_quit_over, button_get_is_mouse_over(scene_title_button_quit));
    sprite_set_is_visible(scene_title_sprite_options_over, button_get_is_mouse_over(scene_title_button_options));
}
void scene_title_draw(void)
{

}

void scene_title_on_released_button_new_game(void)
{
    set_scene(0);
}

void scene_title_on_released_button_load_game(void)
{

}

void scene_title_on_released_button_quit(void)
{
    set_scene(19);
}

void scene_title_on_released_button_options(void)
{

}

/* -------- scene_title -------- */



/* -------- scene_credits -------- */

void scene_credits_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_credits/slide_0000.png", WHITE, true);
    scene_add_sprite(&scene, 0, 0, "resources/scene_credits/slide_0001.png", WHITE, false);
    scene_add_sprite(&scene, 0, 0, "resources/scene_credits/slide_0002.png", WHITE, false);
    scene_add_sprite(&scene, 0, 0, "resources/scene_credits/slide_0003.png", WHITE, false);
    scene_add_sprite(&scene, 0, 0, "resources/scene_credits/slide_0004.png", WHITE, false);
    scene_add_sprite(&scene, 0, 0, "resources/scene_credits/slide_0005.png", WHITE, false);
    scene_add_sprite(&scene, 0, 0, "resources/scene_credits/slide_0006.png", WHITE, false);

    scene_add_button(&scene, 0, 0, 544, 332, BLANK, true, 1,
        NULL, NULL, scene_credits_on_released_button_quit);

    scene_credits_slide_time = 0.0f;
    scene_credits_slide_timer = 0.0f;

    scene_credits_slides_count = 0;

    scene_credits_current_slide_index = 0;
}
void scene_credits_free(void)
{

}

void scene_credits_enter(void)
{
    scene_credits_sprite_slide_0000 = scene_get_sprite(&scene, 0);
    scene_credits_sprite_slide_0001 = scene_get_sprite(&scene, 1);
    scene_credits_sprite_slide_0002 = scene_get_sprite(&scene, 2);
    scene_credits_sprite_slide_0003 = scene_get_sprite(&scene, 3);
    scene_credits_sprite_slide_0004 = scene_get_sprite(&scene, 4);
    scene_credits_sprite_slide_0005 = scene_get_sprite(&scene, 5);
    scene_credits_sprite_slide_0006 = scene_get_sprite(&scene, 6);

    scene_credits_button_quit = scene_get_button(&scene, 0);

    scene_credits_slide_time = 5.0f;
    scene_credits_slide_timer = 0.0f;

    scene_credits_slides_count = 7;
    for (int i = 0; i < scene_credits_slides_count; ++i)
    {
        scene_credits_slides[i] = scene_get_sprite(&scene, i);
    }

    scene_credits_current_slide_index = 0;
}
void scene_credits_exit(void)
{
    scene_credits_sprite_slide_0000 = NULL;
    scene_credits_sprite_slide_0001 = NULL;
    scene_credits_sprite_slide_0002 = NULL;
    scene_credits_sprite_slide_0003 = NULL;
    scene_credits_sprite_slide_0004 = NULL;
    scene_credits_sprite_slide_0005 = NULL;
    scene_credits_sprite_slide_0006 = NULL;

    scene_credits_button_quit = NULL;

    scene_credits_slide_time = 0.0f;
    scene_credits_slide_timer = 0.0f;

    for (int i = 0; i < scene_credits_slides_count; ++i)
    {
        scene_credits_slides[i] = NULL;
    }
    scene_credits_slides_count = 0;

    scene_credits_current_slide_index = 0;
}

void scene_credits_update(float delta)
{
    scene_credits_slide_timer += delta;
    if (scene_credits_slide_timer >= scene_credits_slide_time)
    {
        scene_credits_slide_timer = 0.0f;
        sprite_toggle_is_visible(scene_credits_slides[scene_credits_current_slide_index]);

        if (++scene_credits_current_slide_index < scene_credits_slides_count)
        {
            sprite_toggle_is_visible(scene_credits_slides[scene_credits_current_slide_index]);
        }
        else
        {
            set_scene(-1);
            exit_window = true;
        }
    }
}
void scene_credits_draw(void)
{
    ClearBackground(BLACK);
}

void scene_credits_on_released_button_quit(void)
{
    set_scene(-1);
    exit_window = true;
}

/* -------- scene_credits -------- */



/* -------- scene_0000 -------- */

void scene_0000_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0000/background.png", WHITE, true);

    scene_add_button(&scene, 312, 70, 129, 89, BLANK, true, 4,
        NULL, NULL, scene_0000_on_released_button_exit);
}
void scene_0000_free(void)
{

}

void scene_0000_enter(void)
{
    scene_0000_sprite_background = scene_get_sprite(&scene, 0);

    scene_0000_button_exit = scene_get_button(&scene, 0);
}
void scene_0000_exit(void)
{
    scene_0000_sprite_background = NULL;

    scene_0000_button_exit = NULL;
}

void scene_0000_update(float delta)
{

}
void scene_0000_draw(void)
{

}

void scene_0000_on_released_button_exit(void)
{
    set_scene(1);
}

/* -------- scene_0000 -------- */



/* -------- scene_0001 -------- */

void scene_0001_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0001/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0001_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0001_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0001_on_released_button_exit_2);
}
void scene_0001_free(void)
{

}

void scene_0001_enter(void)
{
    scene_0001_sprite_background = scene_get_sprite(&scene, 0);

    scene_0001_button_exit_0 = scene_get_button(&scene, 0);
    scene_0001_button_exit_1 = scene_get_button(&scene, 1);
    scene_0001_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0001_exit(void)
{
    scene_0001_sprite_background = NULL;

    scene_0001_button_exit_0 = NULL;
    scene_0001_button_exit_1 = NULL;
    scene_0001_button_exit_2 = NULL;
}

void scene_0001_update(float delta)
{

}
void scene_0001_draw(void)
{

}

void scene_0001_on_released_button_exit_0(void)
{
    set_scene(4);
}

void scene_0001_on_released_button_exit_1(void)
{
    set_scene(5);
}

void scene_0001_on_released_button_exit_2(void)
{
    set_scene(2);
}

/* -------- scene_0001 -------- */



/* -------- scene_0002 -------- */

void scene_0002_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0002/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0002_on_released_button_exit_0);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0002_on_released_button_exit_1);
}
void scene_0002_free(void)
{

}

void scene_0002_enter(void)
{
    scene_0002_sprite_background = scene_get_sprite(&scene, 0);

    scene_0002_button_exit_0 = scene_get_button(&scene, 0);
    scene_0002_button_exit_1 = scene_get_button(&scene, 1);
}
void scene_0002_exit(void)
{
    scene_0002_sprite_background = NULL;

    scene_0002_button_exit_0 = NULL;
    scene_0002_button_exit_1 = NULL;
}

void scene_0002_update(float delta)
{

}
void scene_0002_draw(void)
{

}

void scene_0002_on_released_button_exit_0(void)
{
    set_scene(1);
}

void scene_0002_on_released_button_exit_1(void)
{
    set_scene(3);
}

/* -------- scene_0002 -------- */



/* -------- scene_0003 -------- */

void scene_0003_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0003/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0003_on_released_button_exit_0);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0003_on_released_button_exit_1);
}
void scene_0003_free(void)
{

}

void scene_0003_enter(void)
{
    scene_0003_sprite_background = scene_get_sprite(&scene, 0);

    scene_0003_button_exit_0 = scene_get_button(&scene, 0);
    scene_0003_button_exit_1 = scene_get_button(&scene, 1);
}
void scene_0003_exit(void)
{
    scene_0003_sprite_background = NULL;

    scene_0003_button_exit_0 = NULL;
    scene_0003_button_exit_1 = NULL;
}

void scene_0003_update(float delta)
{

}
void scene_0003_draw(void)
{

}

void scene_0003_on_released_button_exit_0(void)
{
    set_scene(2);
}

void scene_0003_on_released_button_exit_1(void)
{
    set_scene(4);
}

/* -------- scene_0003 -------- */



/* -------- scene_0004 -------- */

void scene_0004_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0004/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0004_on_released_button_exit_0);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0004_on_released_button_exit_1);
}
void scene_0004_free(void)
{

}

void scene_0004_enter(void)
{
    scene_0004_sprite_background = scene_get_sprite(&scene, 0);

    scene_0004_button_exit_0 = scene_get_button(&scene, 0);
    scene_0004_button_exit_1 = scene_get_button(&scene, 1);
}
void scene_0004_exit(void)
{
    scene_0004_sprite_background = NULL;

    scene_0004_button_exit_0 = NULL;
    scene_0004_button_exit_1 = NULL;
}

void scene_0004_update(float delta)
{

}
void scene_0004_draw(void)
{

}

void scene_0004_on_released_button_exit_0(void)
{
    set_scene(3);
}

void scene_0004_on_released_button_exit_1(void)
{
    set_scene(1);
}

/* -------- scene_0004 -------- */



/* -------- scene_0005 -------- */

void scene_0005_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0005/background.png", WHITE, true);
    scene_add_sprite(&scene, 352, 183, "resources/scene_0005/lever_down.png", WHITE, true);
    scene_add_sprite(&scene, 352, 183, "resources/scene_0005/lever_up.png", WHITE, true);

    scene_add_button(&scene, 352, 183, 39, 41, BLANK, true, 4,
        NULL, NULL, scene_0005_on_released_button_lever);

    scene_add_button(&scene, 0, 0, 402, 332, BLANK, true, 1,
        NULL, NULL, scene_0005_on_released_button_exit_0);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0005_on_released_button_exit_1);

    scene_0005_sound_lever = LoadSound("resources/scene_0005/lever.ogg");

    scene_0005_is_lever_down = false;
}
void scene_0005_free(void)
{
    UnloadSound(scene_0005_sound_lever);
}

void scene_0005_enter(void)
{
    scene_0005_sprite_background = scene_get_sprite(&scene, 0);
    scene_0005_sprite_lever_down = scene_get_sprite(&scene, 1);
    scene_0005_sprite_lever_up = scene_get_sprite(&scene, 2);

    scene_0005_button_lever = scene_get_button(&scene, 0);
    scene_0005_button_exit_0 = scene_get_button(&scene, 1);
    scene_0005_button_exit_1 = scene_get_button(&scene, 2);

    scene_0005_is_lever_down = true;

    if (!game_data_has_bool(&game_data, "scene_0005_is_lever_down"))
        game_data_add_bool(&game_data, "scene_0005_is_lever_down", scene_0005_is_lever_down);
    else
        scene_0005_is_lever_down = game_data_get_bool(&game_data, "scene_0005_is_lever_down");

    sprite_set_is_visible(scene_0005_sprite_lever_down, scene_0005_is_lever_down);
    sprite_set_is_visible(scene_0005_sprite_lever_up, !scene_0005_is_lever_down);
}
void scene_0005_exit(void)
{
    scene_0005_sprite_background = NULL;
    scene_0005_sprite_lever_down = NULL;
    scene_0005_sprite_lever_up = NULL;

    scene_0005_button_lever = NULL;
    scene_0005_button_exit_0 = NULL;
    scene_0005_button_exit_1 = NULL;

    scene_0005_is_lever_down = false;
}

void scene_0005_update(float delta)
{

}
void scene_0005_draw(void)
{

}

void scene_0005_on_released_button_lever(void)
{
    PlaySound(scene_0005_sound_lever);

    scene_0005_is_lever_down = !scene_0005_is_lever_down;
    game_data_set_bool(&game_data, "scene_0005_is_lever_down", scene_0005_is_lever_down);

    sprite_set_is_visible(scene_0005_sprite_lever_down, scene_0005_is_lever_down);
    sprite_set_is_visible(scene_0005_sprite_lever_up, !scene_0005_is_lever_down);
}

void scene_0005_on_released_button_exit_0(void)
{
    set_scene(7);
}

void scene_0005_on_released_button_exit_1(void)
{
    set_scene(6);
}

/* -------- scene_0005 -------- */



/* -------- scene_0006 -------- */

void scene_0006_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0006/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0006_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0006_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0006_on_released_button_exit_2);
}
void scene_0006_free(void)
{

}

void scene_0006_enter(void)
{
    scene_0006_sprite_background = scene_get_sprite(&scene, 0);

    scene_0006_button_exit_0 = scene_get_button(&scene, 0);
    scene_0006_button_exit_1 = scene_get_button(&scene, 1);
    scene_0006_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0006_exit(void)
{
    scene_0006_sprite_background = NULL;

    scene_0006_button_exit_0 = NULL;
    scene_0006_button_exit_1 = NULL;
    scene_0006_button_exit_2 = NULL;
}

void scene_0006_update(float delta)
{

}
void scene_0006_draw(void)
{

}

void scene_0006_on_released_button_exit_0(void)
{
    set_scene(5);
}

void scene_0006_on_released_button_exit_1(void)
{
    set_scene(3);
}

void scene_0006_on_released_button_exit_2(void)
{
    set_scene(5);
}

/* -------- scene_0006 -------- */



/* -------- scene_0007 -------- */

void scene_0007_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0007/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 402, 332, BLANK, true, 1,
        NULL, NULL, scene_0007_on_released_button_exit_0);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0007_on_released_button_exit_1);
}
void scene_0007_free(void)
{

}

void scene_0007_enter(void)
{
    scene_0007_sprite_background = scene_get_sprite(&scene, 0);

    scene_0007_button_exit_0 = scene_get_button(&scene, 0);
    scene_0007_button_exit_1 = scene_get_button(&scene, 1);
}
void scene_0007_exit(void)
{
    scene_0007_sprite_background = NULL;

    scene_0007_button_exit_0 = NULL;
    scene_0007_button_exit_1 = NULL;
}

void scene_0007_update(float delta)
{

}
void scene_0007_draw(void)
{

}

void scene_0007_on_released_button_exit_0(void)
{
    set_scene(8);
}

void scene_0007_on_released_button_exit_1(void)
{
    set_scene(9);
}

/* -------- scene_0007 -------- */



/* -------- scene_0008 -------- */

void scene_0008_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0008/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0008_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0008_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0008_on_released_button_exit_2);
}
void scene_0008_free(void)
{

}

void scene_0008_enter(void)
{
    scene_0008_sprite_background = scene_get_sprite(&scene, 0);

    scene_0008_button_exit_0 = scene_get_button(&scene, 0);
    scene_0008_button_exit_1 = scene_get_button(&scene, 1);
    scene_0008_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0008_exit(void)
{
    scene_0008_sprite_background = NULL;

    scene_0008_button_exit_0 = NULL;
    scene_0008_button_exit_1 = NULL;
    scene_0008_button_exit_2 = NULL;
}

void scene_0008_update(float delta)
{

}
void scene_0008_draw(void)
{

}

void scene_0008_on_released_button_exit_0(void)
{
    set_scene(10);
}

void scene_0008_on_released_button_exit_1(void)
{

}

void scene_0008_on_released_button_exit_2(void)
{
    set_scene(10);
}

/* -------- scene_0008 -------- */



/* -------- scene_0009 -------- */

void scene_0009_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0009/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0009_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0009_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0009_on_released_button_exit_2);
}
void scene_0009_free(void)
{

}

void scene_0009_enter(void)
{
    scene_0009_sprite_background = scene_get_sprite(&scene, 0);

    scene_0009_button_exit_0 = scene_get_button(&scene, 0);
    scene_0009_button_exit_1 = scene_get_button(&scene, 1);
    scene_0009_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0009_exit(void)
{
    scene_0009_sprite_background = NULL;

    scene_0009_button_exit_0 = NULL;
    scene_0009_button_exit_1 = NULL;
    scene_0009_button_exit_2 = NULL;
}

void scene_0009_update(float delta)
{

}
void scene_0009_draw(void)
{

}

void scene_0009_on_released_button_exit_0(void)
{
    set_scene(12);
}

void scene_0009_on_released_button_exit_1(void)
{
    set_scene(13);
}

void scene_0009_on_released_button_exit_2(void)
{
    set_scene(12);
}

/* -------- scene_0009 -------- */



/* -------- scene_0010 -------- */

void scene_0010_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0010/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0010_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0010_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 166, BLANK, true, 2,
        NULL, NULL, scene_0010_on_released_button_exit_2);

    scene_add_button(&scene, 402, 166, 142, 166, BLANK, true, 3,
        NULL, NULL, scene_0010_on_released_button_exit_3);
}
void scene_0010_free(void)
{

}

void scene_0010_enter(void)
{
    scene_0010_sprite_background = scene_get_sprite(&scene, 0);

    scene_0010_button_exit_0 = scene_get_button(&scene, 0);
    scene_0010_button_exit_1 = scene_get_button(&scene, 1);
    scene_0010_button_exit_2 = scene_get_button(&scene, 2);
    scene_0010_button_exit_3 = scene_get_button(&scene, 3);
}
void scene_0010_exit(void)
{
    scene_0010_sprite_background = NULL;

    scene_0010_button_exit_0 = NULL;
    scene_0010_button_exit_1 = NULL;
    scene_0010_button_exit_2 = NULL;
}

void scene_0010_update(float delta)
{

}
void scene_0010_draw(void)
{

}

void scene_0010_on_released_button_exit_0(void)
{
    set_scene(8);
}

void scene_0010_on_released_button_exit_1(void)
{
    set_scene(9);
}

void scene_0010_on_released_button_exit_2(void)
{
    set_scene(8);
}

void scene_0010_on_released_button_exit_3(void)
{
    set_scene(11);
}

/* -------- scene_0010 -------- */



/* -------- scene_0011 -------- */

void scene_0011_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0011/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0011_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0011_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0011_on_released_button_exit_2);
}
void scene_0011_free(void)
{

}

void scene_0011_enter(void)
{
    scene_0011_sprite_background = scene_get_sprite(&scene, 0);

    scene_0011_button_exit_0 = scene_get_button(&scene, 0);
    scene_0011_button_exit_1 = scene_get_button(&scene, 1);
    scene_0011_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0011_exit(void)
{
    scene_0011_sprite_background = NULL;

    scene_0011_button_exit_0 = NULL;
    scene_0011_button_exit_1 = NULL;
    scene_0011_button_exit_2 = NULL;
}

void scene_0011_update(float delta)
{

}
void scene_0011_draw(void)
{

}

void scene_0011_on_released_button_exit_0(void)
{
    set_scene(9);
}

void scene_0011_on_released_button_exit_1(void)
{
    set_scene(6);
}

void scene_0011_on_released_button_exit_2(void)
{
    set_scene(8);
}

/* -------- scene_0011 -------- */



/* -------- scene_0012 -------- */

void scene_0012_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0012/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0012_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0012_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0012_on_released_button_exit_2);
}
void scene_0012_free(void)
{

}

void scene_0012_enter(void)
{
    scene_0012_sprite_background = scene_get_sprite(&scene, 0);

    scene_0012_button_exit_0 = scene_get_button(&scene, 0);
    scene_0012_button_exit_1 = scene_get_button(&scene, 1);
    scene_0012_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0012_exit(void)
{
    scene_0012_sprite_background = NULL;

    scene_0012_button_exit_0 = NULL;
    scene_0012_button_exit_1 = NULL;
    scene_0012_button_exit_2 = NULL;
}

void scene_0012_update(float delta)
{

}
void scene_0012_draw(void)
{

}

void scene_0012_on_released_button_exit_0(void)
{
    set_scene(9);
}

void scene_0012_on_released_button_exit_1(void)
{
    set_scene(8);
}

void scene_0012_on_released_button_exit_2(void)
{
    set_scene(9);
}

/* -------- scene_0012 -------- */



/* -------- scene_0013 -------- */

void scene_0013_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0013/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0013_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0013_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0013_on_released_button_exit_2);
}
void scene_0013_free(void)
{

}

void scene_0013_enter(void)
{
    scene_0013_sprite_background = scene_get_sprite(&scene, 0);

    scene_0013_button_exit_0 = scene_get_button(&scene, 0);
    scene_0013_button_exit_1 = scene_get_button(&scene, 1);
    scene_0013_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0013_exit(void)
{
    scene_0013_sprite_background = NULL;

    scene_0013_button_exit_0 = NULL;
    scene_0013_button_exit_1 = NULL;
    scene_0013_button_exit_2 = NULL;
}

void scene_0013_update(float delta)
{

}
void scene_0013_draw(void)
{

}

void scene_0013_on_released_button_exit_0(void)
{
    set_scene(14);
}

void scene_0013_on_released_button_exit_1(void)
{
    set_scene(15);
}

void scene_0013_on_released_button_exit_2(void)
{
    set_scene(14);
}

/* -------- scene_0013 -------- */



/* -------- scene_0014 -------- */

void scene_0014_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0014/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0014_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0014_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0014_on_released_button_exit_2);
}
void scene_0014_free(void)
{

}

void scene_0014_enter(void)
{
    scene_0014_sprite_background = scene_get_sprite(&scene, 0);

    scene_0014_button_exit_0 = scene_get_button(&scene, 0);
    scene_0014_button_exit_1 = scene_get_button(&scene, 1);
    scene_0014_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0014_exit(void)
{
    scene_0014_sprite_background = NULL;

    scene_0014_button_exit_0 = NULL;
    scene_0014_button_exit_1 = NULL;
    scene_0014_button_exit_2 = NULL;
}

void scene_0014_update(float delta)
{

}
void scene_0014_draw(void)
{

}

void scene_0014_on_released_button_exit_0(void)
{
    set_scene(13);
}

void scene_0014_on_released_button_exit_1(void)
{
    set_scene(12);
}

void scene_0014_on_released_button_exit_2(void)
{
    set_scene(13);
}

/* -------- scene_0014 -------- */



/* -------- scene_0015 -------- */

void scene_0015_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0015/background.png", WHITE, true);
    scene_add_sprite(&scene, 38, 192, "resources/scene_0015/lever_down.png", WHITE, true);
    scene_add_sprite(&scene, 38, 192, "resources/scene_0015/lever_up.png", WHITE, true);

    scene_add_button(&scene, 38, 192, 99, 73, BLANK, true, 4,
        NULL, NULL, scene_0015_on_released_button_lever);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0015_on_released_button_exit_0);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0015_on_released_button_exit_1);

    scene_0015_sound_lever = LoadSound("resources/scene_0015/lever.ogg");

    scene_0015_is_lever_down = false;
}
void scene_0015_free(void)
{
    UnloadSound(scene_0015_sound_lever);
}

void scene_0015_enter(void)
{
    scene_0015_sprite_background = scene_get_sprite(&scene, 0);
    scene_0015_sprite_lever_down = scene_get_sprite(&scene, 1);
    scene_0015_sprite_lever_up = scene_get_sprite(&scene, 2);

    scene_0015_button_lever = scene_get_button(&scene, 0);
    scene_0015_button_exit_0 = scene_get_button(&scene, 0);
    scene_0015_button_exit_1 = scene_get_button(&scene, 1);

    scene_0015_is_lever_down = true;

    if (!game_data_has_bool(&game_data, "scene_0015_is_lever_down"))
        game_data_add_bool(&game_data, "scene_0015_is_lever_down", scene_0015_is_lever_down);
    else
        scene_0015_is_lever_down = game_data_get_bool(&game_data, "scene_0015_is_lever_down");

    sprite_set_is_visible(scene_0015_sprite_lever_down, scene_0015_is_lever_down);
    sprite_set_is_visible(scene_0015_sprite_lever_up, !scene_0015_is_lever_down);
}
void scene_0015_exit(void)
{
    scene_0015_sprite_background = NULL;
    scene_0015_sprite_lever_down = NULL;
    scene_0015_sprite_lever_up = NULL;

    scene_0015_button_lever = NULL;
    scene_0015_button_exit_0 = NULL;
    scene_0015_button_exit_1 = NULL;

    scene_0015_is_lever_down = false;
}

void scene_0015_update(float delta)
{

}
void scene_0015_draw(void)
{

}

void scene_0015_on_released_button_lever(void)
{
    PlaySound(scene_0015_sound_lever);

    scene_0015_is_lever_down = !scene_0015_is_lever_down;
    game_data_set_bool(&game_data, "scene_0015_is_lever_down", scene_0015_is_lever_down);

    sprite_set_is_visible(scene_0015_sprite_lever_down, scene_0015_is_lever_down);
    sprite_set_is_visible(scene_0015_sprite_lever_up, !scene_0015_is_lever_down);
}

void scene_0015_on_released_button_exit_0(void)
{
    set_scene(17);
}

void scene_0015_on_released_button_exit_1(void)
{
    set_scene(16);
}

/* -------- scene_0015 -------- */



/* -------- scene_0016 -------- */

void scene_0016_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0016/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0016_on_released_button_exit_0);

    scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 1,
        NULL, NULL, scene_0016_on_released_button_exit_1);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2,
        NULL, NULL, scene_0016_on_released_button_exit_2);
}
void scene_0016_free(void)
{

}

void scene_0016_enter(void)
{
    scene_0016_sprite_background = scene_get_sprite(&scene, 0);

    scene_0016_button_exit_0 = scene_get_button(&scene, 0);
    scene_0016_button_exit_1 = scene_get_button(&scene, 1);
    scene_0016_button_exit_2 = scene_get_button(&scene, 2);
}
void scene_0016_exit(void)
{
    scene_0016_sprite_background = NULL;

    scene_0016_button_exit_0 = NULL;
    scene_0016_button_exit_1 = NULL;
    scene_0016_button_exit_2 = NULL;
}

void scene_0016_update(float delta)
{

}
void scene_0016_draw(void)
{

}

void scene_0016_on_released_button_exit_0(void)
{
    set_scene(15);
}

void scene_0016_on_released_button_exit_1(void)
{
    set_scene(14);
}

void scene_0016_on_released_button_exit_2(void)
{
    set_scene(17);
}

/* -------- scene_0016 -------- */



/* -------- scene_0017 -------- */

void scene_0017_init(void)
{
    scene_add_sprite(&scene, 0, 0, "resources/scene_0017/background.png", WHITE, true);

    scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 0,
        NULL, NULL, scene_0017_on_released_button_exit_0);

    scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 1,
        NULL, NULL, scene_0017_on_released_button_exit_1);
}
void scene_0017_free(void)
{

}

void scene_0017_enter(void)
{
    scene_0017_sprite_background = scene_get_sprite(&scene, 0);

    scene_0017_button_exit_0 = scene_get_button(&scene, 0);
    scene_0017_button_exit_1 = scene_get_button(&scene, 1);
}
void scene_0017_exit(void)
{
    scene_0017_sprite_background = NULL;

    scene_0017_button_exit_0 = NULL;
    scene_0017_button_exit_1 = NULL;
    scene_0017_button_exit_2 = NULL;
}

void scene_0017_update(float delta)
{

}
void scene_0017_draw(void)
{

}

void scene_0017_on_released_button_exit_0(void)
{
    set_scene(16);
}

void scene_0017_on_released_button_exit_1(void)
{
    set_scene(15);
}

/* -------- scene_0017 -------- */
