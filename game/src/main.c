#include "array.h"
#include "button.h"
#include "game_data.h"
#include "scene.h"
#include "sprite.h"

#include "scene_0000.h"
#include "scene_0001.h"

#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



bool exit_window;

struct game_data game_data;

float elapsed_time;

bool is_enabled_mouse;
bool is_draw_mouse;

Texture2D mouse_cursor_textures[5];
Vector2 mouse_cursor_offsets[5];

int current_mouse_cursor_index;

struct array scenes;
struct array active_scenes;

RenderTexture2D render_texture;

struct button * current_button;



void game_init(void);
void game_free(void);
void game_reset(void);

void game_update(float delta);
void game_update_scene(struct scene * scene, float delta);

void game_draw(void);
void game_draw_scene(struct scene * scene);
void game_draw_mouse(void);
void game_draw_render_texture(void);

void add_scene(int id, char * name, int x, int y, bool is_update, bool is_draw, void(*scene_load)(struct scene * scene), void(*scene_unload)(struct scene * scene), void(*scene_enter)(struct scene * scene), void(*scene_exit)(struct scene * scene), void(*scene_update)(struct scene * scene, float delta), void(*scene_draw)(struct scene * scene));



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

    elapsed_time = 0.0f;

    is_enabled_mouse = false;
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

    scenes = array_create(2, sizeof(struct scene));
    active_scenes = array_create(2, sizeof(struct scene *));

    add_scene(0, "scene_0000", 0, 0, true, true, scene_0000_load, scene_0000_unload, scene_0000_enter, scene_0000_exit, scene_0000_update, scene_0000_draw);
    add_scene(1, "scene_0001", 0, 0, false, true, scene_0001_load, scene_0001_unload, scene_0001_enter, scene_0001_exit, scene_0001_update, scene_0001_draw);

    for (int i = array_get_count(&scenes) - 1; i >= 0; --i)
    {
        struct scene * scene = (struct scene *)array_get(&scenes, i);
        scene_load(scene);
        scene_enter(scene);
        array_append(&active_scenes, &scene);
    }

    render_texture = LoadRenderTexture(544, 332);

    current_button = NULL;
}
void game_free(void)
{
    printf("game_free\n");

    array_free(&active_scenes);

    for (int i = 0; i < array_get_count(&scenes); ++i)
    {
        struct scene * scene = (struct scene *)array_get(&scenes, i);
        scene_exit(scene);
        scene_unload(scene);
        scene_free(scene);
    }

    array_free(&scenes);

    game_data_free(&game_data);
    game_data = (struct game_data){ 0 };

    elapsed_time = 0.0f;

    is_enabled_mouse = false;
    is_draw_mouse = false;

    for (int i = 0; i < 4; ++i)
    {
        UnloadTexture(mouse_cursor_textures[i]);
        mouse_cursor_offsets[0] = (Vector2){ 0.0f, 0.0f };
    }

    current_mouse_cursor_index = -1;

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

    for (int i = 0; i < array_get_count(&active_scenes); ++i)
    {
        struct scene * scene = *(struct scene **)array_get(&active_scenes, i);
        if (scene_get_is_update(scene))
        {
            game_update_scene(scene, delta);
        }
    }
}
void game_update_scene(struct scene * scene, float delta)
{
    scene_translate_elapsed_time(scene, delta);

    current_mouse_cursor_index = 1;

    if (is_enabled_mouse)
    {
        Vector2 mouse_position = GetMousePosition();

        struct button * ptr = NULL;

        for (int i = 0; i < scene_get_buttons_count(scene); ++i)
        {
            struct button * button = scene_get_button_from_index(scene, i);

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
                int x = scene_get_x(scene) + button_get_x(button);
                int y = scene_get_y(scene) + button_get_y(button);
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

    scene_update(scene, delta);
}

void game_draw(void)
{
    BeginTextureMode(render_texture);

    ClearBackground((Color) { 255, 0, 255, 255 });

    for (int i = 0; i < array_get_count(&active_scenes); ++i)
    {
        struct scene * scene = *(struct scene **)array_get(&active_scenes, i);
        if (scene_get_is_draw(scene))
        {
            game_draw_scene(scene);
        }
    }

    if (is_draw_mouse)
    {
        game_draw_mouse();
    }

    EndTextureMode();

    BeginDrawing();

    ClearBackground(BLACK);

    game_draw_render_texture();

    EndDrawing();
}
void game_draw_scene(struct scene * scene)
{
    scene_draw(scene);
}
void game_draw_mouse(void)
{
    Vector2 mouse_position = GetMousePosition();
    mouse_position.x += mouse_cursor_offsets[current_mouse_cursor_index].x;
    mouse_position.y += mouse_cursor_offsets[current_mouse_cursor_index].y;
    DrawTexture(mouse_cursor_textures[current_mouse_cursor_index], (int)mouse_position.x, (int)mouse_position.y, WHITE);
}
void game_draw_render_texture(void)
{
    Rectangle source = (Rectangle){ 0.0f, 0.0f, (float)render_texture.texture.width, -(float)render_texture.texture.height };
    Rectangle dest = (Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    DrawTexturePro(render_texture.texture, source, dest, (Vector2) { 0.0f, 0.0f }, 0.0f, WHITE);
}

void add_scene(int id, char * name, int x, int y, bool is_update, bool is_draw, void(*scene_load)(struct scene * scene), void(*scene_unload)(struct scene * scene), void(*scene_enter)(struct scene * scene), void(*scene_exit)(struct scene * scene), void(*scene_update)(struct scene * scene, float delta), void(*scene_draw)(struct scene * scene))
{
    struct scene scene = scene_create(id, name, x, y, is_update, is_draw, scene_load, scene_unload, scene_enter, scene_exit, scene_update, scene_draw);
    array_append(&scenes, &scene);
}
