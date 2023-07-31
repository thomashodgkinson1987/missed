#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "array.h"
#include "button.h"
#include "sprite.h"
#include "scene.h"



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

float elapsed_time;

bool is_mouse_input_enabled;
bool is_draw_mouse;

Texture2D mouse_cursor_textures[5];
Vector2 mouse_cursor_offsets[5];

int current_mouse_cursor_index;

int current_scene_index;
int next_scene_index;

bool is_scene_transition;
enum scene_transision_enum scene_transision_state;
float scene_transition_fade_out_time;
float scene_transition_wait_time;
float scene_transition_fade_in_time;
float scene_transition_timer;
Color scene_transition_color;

void (*scene_init_function_pointers[7])(void);
void (*scene_free_function_pointers[7])(void);
void (*scene_reset_function_pointers[7])(void);
void (*scene_enter_function_pointers[7])(void);
void (*scene_exit_function_pointers[7])(void);
void (*scene_update_function_pointers[7])(float delta);
void (*scene_draw_function_pointers[7])(void);



bool is_draw_debug;



void game_init(void);
void game_free(void);
void game_reset(void);

void game_update(float delta);
void game_draw(void);



void game_scene_init(int index);
void game_scene_free(int index);
void game_scene_reset(int index);

void game_scene_enter(int index);
void game_scene_exit(int index);

void game_scene_update(int index, float delta);
void game_scene_draw(int index);



void set_scene(int index);



/* -------- scene_0 -------- */

struct scene scene_0;

void scene_0_init(void);
void scene_0_free(void);
void scene_0_reset(void);

void scene_0_enter(void);
void scene_0_exit(void);

void scene_0_update(float delta);
void scene_0_draw(void);

void scene_0_on_button_0_pressed(void);

/* -------- scene_0 -------- */



/* -------- scene_1 -------- */

struct scene scene_1;

void scene_1_init(void);
void scene_1_free(void);
void scene_1_reset(void);

void scene_1_enter(void);
void scene_1_exit(void);

void scene_1_update(float delta);
void scene_1_draw(void);

void scene_1_on_button_0_pressed(void);
void scene_1_on_button_1_pressed(void);
void scene_1_on_button_2_pressed(void);

/* -------- scene_1 -------- */



/* -------- scene_2 -------- */

struct scene scene_2;

void scene_2_init(void);
void scene_2_free(void);
void scene_2_reset(void);

void scene_2_enter(void);
void scene_2_exit(void);

void scene_2_update(float delta);
void scene_2_draw(void);

void scene_2_on_button_0_pressed(void);
void scene_2_on_button_1_pressed(void);

/* -------- scene_2 -------- */



/* -------- scene_3 -------- */

struct scene scene_3;

void scene_3_init(void);
void scene_3_free(void);
void scene_3_reset(void);

void scene_3_enter(void);
void scene_3_exit(void);

void scene_3_update(float delta);
void scene_3_draw(void);

void scene_3_on_button_0_pressed(void);
void scene_3_on_button_1_pressed(void);

/* -------- scene_3 -------- */



/* -------- scene_4 -------- */

struct scene scene_4;

void scene_4_init(void);
void scene_4_free(void);
void scene_4_reset(void);

void scene_4_enter(void);
void scene_4_exit(void);

void scene_4_update(float delta);
void scene_4_draw(void);

void scene_4_on_button_0_pressed(void);
void scene_4_on_button_1_pressed(void);

/* -------- scene_4 -------- */



/* -------- scene_5 -------- */

struct scene scene_5;

struct sprite scene_5_sprite_lever_up;
bool scene_5_is_lever_up;

void scene_5_init(void);
void scene_5_free(void);
void scene_5_reset(void);

void scene_5_enter(void);
void scene_5_exit(void);

void scene_5_update(float delta);
void scene_5_draw(void);

void scene_5_on_button_0_pressed(void);
void scene_5_on_button_1_pressed(void);
void scene_5_on_button_2_pressed(void);

/* -------- scene_5 -------- */



/* -------- scene_6 -------- */

struct scene scene_6;

void scene_6_init(void);
void scene_6_free(void);
void scene_6_reset(void);

void scene_6_enter(void);
void scene_6_exit(void);

void scene_6_update(float delta);
void scene_6_draw(void);

void scene_6_on_button_0_pressed(void);
void scene_6_on_button_1_pressed(void);
void scene_6_on_button_2_pressed(void);

/* -------- scene_6 -------- */



int main(void)
{
    InitWindow(512, 512, "Missed");
    SetTargetFPS(60);
    HideCursor();

    game_init();

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        game_update(delta);
        game_draw();
    }

    game_free();

    CloseWindow();

    return 0;
}



void game_init(void)
{
    printf("game_init\n");

    elapsed_time = 0.0f;

    is_mouse_input_enabled = false;
    is_draw_mouse = true;

    mouse_cursor_textures[0] = LoadTexture("resources/mouse_cursor_0000.png");
    mouse_cursor_textures[1] = LoadTexture("resources/mouse_cursor_0001.png");
    mouse_cursor_textures[2] = LoadTexture("resources/mouse_cursor_0002.png");
    mouse_cursor_textures[3] = LoadTexture("resources/mouse_cursor_0003.png");
    mouse_cursor_textures[4] = LoadTexture("resources/mouse_cursor_0004.png");
    mouse_cursor_offsets[0] = (Vector2){ -8.0f, -2.0f };
    mouse_cursor_offsets[1] = (Vector2){ -8.0f, -2.0f };
    mouse_cursor_offsets[2] = (Vector2){ -15.0f, -8.0f };
    mouse_cursor_offsets[3] = (Vector2){ -2.0f, -8.0f };
    mouse_cursor_offsets[4] = (Vector2){ -8.0f, -15.0f };

    current_mouse_cursor_index = 0;

    current_scene_index = -1;
    next_scene_index = 0;

    is_scene_transition = true;
    scene_transision_state = SCENE_TRANSITION_RUN;
    scene_transition_fade_out_time = 0.0f;
    scene_transition_wait_time = 0.0f;
    scene_transition_fade_in_time = 0.0f;
    scene_transition_timer = 0.0f;
    scene_transition_color = BLACK;
    scene_transition_color.a = 255;

    scene_init_function_pointers[0] = scene_0_init;
    scene_free_function_pointers[0] = scene_0_free;
    scene_reset_function_pointers[0] = scene_0_reset;
    scene_enter_function_pointers[0] = scene_0_enter;
    scene_exit_function_pointers[0] = scene_0_exit;
    scene_update_function_pointers[0] = scene_0_update;
    scene_draw_function_pointers[0] = scene_0_draw;

    scene_init_function_pointers[1] = scene_1_init;
    scene_free_function_pointers[1] = scene_1_free;
    scene_reset_function_pointers[1] = scene_1_reset;
    scene_enter_function_pointers[1] = scene_1_enter;
    scene_exit_function_pointers[1] = scene_1_exit;
    scene_update_function_pointers[1] = scene_1_update;
    scene_draw_function_pointers[1] = scene_1_draw;

    scene_init_function_pointers[2] = scene_2_init;
    scene_free_function_pointers[2] = scene_2_free;
    scene_reset_function_pointers[2] = scene_2_reset;
    scene_enter_function_pointers[2] = scene_2_enter;
    scene_exit_function_pointers[2] = scene_2_exit;
    scene_update_function_pointers[2] = scene_2_update;
    scene_draw_function_pointers[2] = scene_2_draw;

    scene_init_function_pointers[3] = scene_3_init;
    scene_free_function_pointers[3] = scene_3_free;
    scene_reset_function_pointers[3] = scene_3_reset;
    scene_enter_function_pointers[3] = scene_3_enter;
    scene_exit_function_pointers[3] = scene_3_exit;
    scene_update_function_pointers[3] = scene_3_update;
    scene_draw_function_pointers[3] = scene_3_draw;

    scene_init_function_pointers[4] = scene_4_init;
    scene_free_function_pointers[4] = scene_4_free;
    scene_reset_function_pointers[4] = scene_4_reset;
    scene_enter_function_pointers[4] = scene_4_enter;
    scene_exit_function_pointers[4] = scene_4_exit;
    scene_update_function_pointers[4] = scene_4_update;
    scene_draw_function_pointers[4] = scene_4_draw;

    scene_init_function_pointers[5] = scene_5_init;
    scene_free_function_pointers[5] = scene_5_free;
    scene_reset_function_pointers[5] = scene_5_reset;
    scene_enter_function_pointers[5] = scene_5_enter;
    scene_exit_function_pointers[5] = scene_5_exit;
    scene_update_function_pointers[5] = scene_5_update;
    scene_draw_function_pointers[5] = scene_5_draw;

    scene_init_function_pointers[6] = scene_6_init;
    scene_free_function_pointers[6] = scene_6_free;
    scene_reset_function_pointers[6] = scene_6_reset;
    scene_enter_function_pointers[6] = scene_6_enter;
    scene_exit_function_pointers[6] = scene_6_exit;
    scene_update_function_pointers[6] = scene_6_update;
    scene_draw_function_pointers[6] = scene_6_draw;

    is_draw_debug = true;
}
void game_free(void)
{
    printf("game_free\n");

    if (current_scene_index != -1)
    {
        game_scene_free(current_scene_index);
    }

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
    scene_transision_state = SCENE_TRANSITION_IDLE;
    scene_transition_fade_out_time = 0.0f;
    scene_transition_wait_time = 0.0f;
    scene_transition_fade_in_time = 0.0f;
    scene_transition_timer = 0.0f;
    scene_transition_color = BLANK;

    scene_init_function_pointers[0] = NULL;
    scene_free_function_pointers[0] = NULL;
    scene_reset_function_pointers[0] = NULL;
    scene_enter_function_pointers[0] = NULL;
    scene_exit_function_pointers[0] = NULL;
    scene_update_function_pointers[0] = NULL;
    scene_draw_function_pointers[0] = NULL;

    scene_init_function_pointers[1] = NULL;
    scene_free_function_pointers[1] = NULL;
    scene_reset_function_pointers[1] = NULL;
    scene_enter_function_pointers[1] = NULL;
    scene_exit_function_pointers[1] = NULL;
    scene_update_function_pointers[1] = NULL;
    scene_draw_function_pointers[1] = NULL;

    scene_init_function_pointers[2] = NULL;
    scene_free_function_pointers[2] = NULL;
    scene_reset_function_pointers[2] = NULL;
    scene_enter_function_pointers[2] = NULL;
    scene_exit_function_pointers[2] = NULL;
    scene_update_function_pointers[2] = NULL;
    scene_draw_function_pointers[2] = NULL;

    scene_init_function_pointers[3] = NULL;
    scene_free_function_pointers[3] = NULL;
    scene_reset_function_pointers[3] = NULL;
    scene_enter_function_pointers[3] = NULL;
    scene_exit_function_pointers[3] = NULL;
    scene_update_function_pointers[3] = NULL;
    scene_draw_function_pointers[3] = NULL;

    scene_init_function_pointers[4] = NULL;
    scene_free_function_pointers[4] = NULL;
    scene_reset_function_pointers[4] = NULL;
    scene_enter_function_pointers[4] = NULL;
    scene_exit_function_pointers[4] = NULL;
    scene_update_function_pointers[4] = NULL;
    scene_draw_function_pointers[4] = NULL;

    scene_init_function_pointers[5] = NULL;
    scene_free_function_pointers[5] = NULL;
    scene_reset_function_pointers[5] = NULL;
    scene_enter_function_pointers[5] = NULL;
    scene_exit_function_pointers[5] = NULL;
    scene_update_function_pointers[5] = NULL;
    scene_draw_function_pointers[5] = NULL;

    scene_init_function_pointers[6] = NULL;
    scene_free_function_pointers[6] = NULL;
    scene_reset_function_pointers[6] = NULL;
    scene_enter_function_pointers[6] = NULL;
    scene_exit_function_pointers[6] = NULL;
    scene_update_function_pointers[6] = NULL;
    scene_draw_function_pointers[6] = NULL;

    is_draw_debug = false;
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
        if (scene_transision_state == SCENE_TRANSITION_START)
        {
            scene_transition_timer = 0.0f;
            scene_transition_color.a = 0;
            scene_transision_state = SCENE_TRANSITION_FADE_OUT;
        }
        if (scene_transision_state == SCENE_TRANSITION_FADE_OUT)
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
                scene_transision_state = SCENE_TRANSITION_RUN;
            }
        }
        if (scene_transision_state == SCENE_TRANSITION_RUN)
        {
            if (current_scene_index != -1)
            {
                game_scene_exit(current_scene_index);
                game_scene_free(current_scene_index);
            }
            current_scene_index = next_scene_index;
            next_scene_index = -1;
            if (current_scene_index != -1)
            {
                game_scene_init(current_scene_index);
                game_scene_enter(current_scene_index);
            }
            scene_transision_state = SCENE_TRANSITION_WAIT;
        }
        if (scene_transision_state == SCENE_TRANSITION_WAIT)
        {
            scene_transition_timer += delta;
            if (scene_transition_timer >= scene_transition_wait_time)
            {
                scene_transition_timer = 0.0f;
                scene_transision_state = SCENE_TRANSITION_FADE_IN;
            }
        }
        if (scene_transision_state == SCENE_TRANSITION_FADE_IN)
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
                scene_transision_state = SCENE_TRANSITION_END;
            }
        }
        if (scene_transision_state == SCENE_TRANSITION_END)
        {
            is_mouse_input_enabled = true;
            is_scene_transition = false;
            scene_transision_state = SCENE_TRANSITION_IDLE;
        }
    }

    if (current_scene_index != -1)
    {
        game_scene_update(current_scene_index, delta);
    }
}
void game_draw(void)
{
    BeginDrawing();

    ClearBackground(WHITE);

    if (current_scene_index != -1)
    {
        game_scene_draw(current_scene_index);
    }

    if (is_draw_mouse)
    {
        Vector2 mouse_position = GetMousePosition();
        mouse_position.x += mouse_cursor_offsets[current_mouse_cursor_index].x;
        mouse_position.y += mouse_cursor_offsets[current_mouse_cursor_index].y;
        DrawTexture(mouse_cursor_textures[current_mouse_cursor_index], mouse_position.x, mouse_position.y, WHITE);
    }

    if (is_scene_transition)
    {
        DrawRectangle(0, 0, 512, 512, scene_transition_color);
    }

    if (is_draw_debug)
    {
        DrawRectangle(0, 0, 138, 26, BLACK);
        DrawText(TextFormat("current_scene_index: %d", current_scene_index), 8, 8, 8, WHITE);
    }

    EndDrawing();
}



void game_scene_init(int index)
{
    printf("scene_init: index=%d\n", index);

    (*scene_init_function_pointers[index])();
}
void game_scene_free(int index)
{
    printf("scene_free: index=%d\n", index);

    (*scene_free_function_pointers[index])();
}
void game_scene_reset(int index)
{
    printf("scene_reset: index=%d\n", index);

    (*scene_reset_function_pointers[index])();
}

void game_scene_enter(int index)
{
    printf("scene_enter: index=%d\n", index);

    (*scene_enter_function_pointers[index])();
}
void game_scene_exit(int index)
{
    printf("scene_exit: index=%d\n", index);

    (*scene_exit_function_pointers[index])();
}

void game_scene_update(int index, float delta)
{
    (*scene_update_function_pointers[index])(delta);
}
void game_scene_draw(int index)
{
    (*scene_draw_function_pointers[index])();
}



void set_scene(int index)
{
    printf("set_scene: index=%d\n", index);

    is_mouse_input_enabled = false;
    next_scene_index = index;
    is_scene_transition = true;
    scene_transision_state = SCENE_TRANSITION_START;
}



/* -------- scene_0 -------- */

void scene_0_init(void)
{
    scene_0 = scene_create(LoadTexture("resources/scene_0_background.png"));
    scene_init(&scene_0);

    scene_add_button(&scene_0, 306, 154, 138, 94, BLANK, true, 1, scene_0_on_button_0_pressed);
}
void scene_0_free(void)
{
    scene_free(&scene_0);
}
void scene_0_reset(void)
{
    scene_0_free();
    scene_0_init();
}

void scene_0_enter(void)
{

}
void scene_0_exit(void)
{

}

void scene_0_update(float delta)
{
    scene_translate_elapsed_time(&scene_0, delta);

    current_mouse_cursor_index = 0;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        for (int i = 0; i < scene_get_buttons_count(&scene_0); ++i)
        {
            struct button * button = scene_get_button(&scene_0, i);

            if (!button_get_is_enabled(button))
                continue;

            int x = button_get_x(button);
            int y = button_get_y(button);
            int width = button_get_width(button);
            int height = button_get_height(button);

            if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
            {
                current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    button_get_on_pressed(button)();
                }
                break;
            }
        }
    }
}
void scene_0_draw(void)
{
    DrawTexture(scene_get_background_texture(&scene_0), 0, 0, WHITE);

    for (int i = 0; i < scene_get_buttons_count(&scene_0); ++i)
    {
        struct button * button = scene_get_button(&scene_0, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }
}

void scene_0_on_button_0_pressed(void)
{
    set_scene(1);
}

/* -------- scene_0 -------- */



/* -------- scene_1 -------- */

void scene_1_init(void)
{
    scene_1 = scene_create(LoadTexture("resources/scene_1_background.png"));
    scene_init(&scene_1);

    scene_add_button(&scene_1, 0, 0, 132, 512, BLANK, true, 3, scene_1_on_button_0_pressed);
    scene_add_button(&scene_1, 132, 0, 248, 512, BLANK, true, 0, scene_1_on_button_1_pressed);
    scene_add_button(&scene_1, 380, 0, 132, 512, BLANK, true, 2, scene_1_on_button_2_pressed);
}
void scene_1_free(void)
{
    scene_free(&scene_1);
}
void scene_1_reset(void)
{
    scene_1_free();
    scene_1_init();
}

void scene_1_enter(void)
{

}
void scene_1_exit(void)
{

}

void scene_1_update(float delta)
{
    scene_translate_elapsed_time(&scene_1, delta);

    current_mouse_cursor_index = 0;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        for (int i = 0; i < scene_get_buttons_count(&scene_1); ++i)
        {
            struct button * button = scene_get_button(&scene_1, i);

            if (!button_get_is_enabled(button))
                continue;

            int x = button_get_x(button);
            int y = button_get_y(button);
            int width = button_get_width(button);
            int height = button_get_height(button);

            if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
            {
                current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    button_get_on_pressed(button)();
                }
                break;
            }
        }
    }
}
void scene_1_draw(void)
{
    DrawTexture(scene_get_background_texture(&scene_1), 0, 0, WHITE);

    for (int i = 0; i < scene_get_buttons_count(&scene_1); ++i)
    {
        struct button * button = scene_get_button(&scene_1, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }
}

void scene_1_on_button_0_pressed(void)
{
    set_scene(4);
}
void scene_1_on_button_1_pressed(void)
{
    set_scene(5);
}
void scene_1_on_button_2_pressed(void)
{
    set_scene(2);
}

/* -------- scene_1 -------- */



/* -------- scene_2 -------- */

void scene_2_init(void)
{
    scene_2 = scene_create(LoadTexture("resources/scene_2_background.png"));
    scene_init(&scene_2);

    scene_add_button(&scene_2, 0, 0, 132, 512, BLANK, true, 3, scene_2_on_button_0_pressed);
    scene_add_button(&scene_2, 380, 0, 132, 512, BLANK, true, 2, scene_2_on_button_1_pressed);
}
void scene_2_free(void)
{
    scene_free(&scene_2);
}
void scene_2_reset(void)
{
    scene_2_free();
    scene_2_init();
}

void scene_2_enter(void)
{

}
void scene_2_exit(void)
{

}

void scene_2_update(float delta)
{
    scene_translate_elapsed_time(&scene_2, delta);

    current_mouse_cursor_index = 0;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        for (int i = 0; i < scene_get_buttons_count(&scene_2); ++i)
        {
            struct button * button = scene_get_button(&scene_2, i);

            if (!button_get_is_enabled(button))
                continue;

            int x = button_get_x(button);
            int y = button_get_y(button);
            int width = button_get_width(button);
            int height = button_get_height(button);

            if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
            {
                current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    button_get_on_pressed(button)();
                }
                break;
            }
        }
    }
}
void scene_2_draw(void)
{
    DrawTexture(scene_get_background_texture(&scene_2), 0, 0, WHITE);

    for (int i = 0; i < scene_get_buttons_count(&scene_2); ++i)
    {
        struct button * button = scene_get_button(&scene_2, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }
}

void scene_2_on_button_0_pressed(void)
{
    set_scene(1);
}
void scene_2_on_button_1_pressed(void)
{
    set_scene(3);
}

/* -------- scene_2 -------- */



/* -------- scene_3 -------- */

void scene_3_init(void)
{
    scene_3 = scene_create(LoadTexture("resources/scene_3_background.png"));
    scene_init(&scene_3);

    scene_add_button(&scene_3, 0, 0, 132, 512, BLANK, true, 3, scene_3_on_button_0_pressed);
    scene_add_button(&scene_3, 380, 0, 132, 512, BLANK, true, 2, scene_3_on_button_1_pressed);
}
void scene_3_free(void)
{
    scene_free(&scene_3);
}
void scene_3_reset(void)
{
    scene_3_free();
    scene_3_init();
}

void scene_3_enter(void)
{

}
void scene_3_exit(void)
{

}

void scene_3_update(float delta)
{
    scene_translate_elapsed_time(&scene_3, delta);

    current_mouse_cursor_index = 0;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        for (int i = 0; i < scene_get_buttons_count(&scene_3); ++i)
        {
            struct button * button = scene_get_button(&scene_3, i);

            if (!button_get_is_enabled(button))
                continue;

            int x = button_get_x(button);
            int y = button_get_y(button);
            int width = button_get_width(button);
            int height = button_get_height(button);

            if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
            {
                current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    button_get_on_pressed(button)();
                }
                break;
            }
        }
    }
}
void scene_3_draw(void)
{
    DrawTexture(scene_get_background_texture(&scene_3), 0, 0, WHITE);

    for (int i = 0; i < scene_get_buttons_count(&scene_3); ++i)
    {
        struct button * button = scene_get_button(&scene_3, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }
}

void scene_3_on_button_0_pressed(void)
{
    set_scene(2);
}
void scene_3_on_button_1_pressed(void)
{
    set_scene(4);
}

/* -------- scene_3 -------- */



/* -------- scene_4 -------- */

void scene_4_init(void)
{
    scene_4 = scene_create(LoadTexture("resources/scene_4_background.png"));
    scene_init(&scene_4);

    scene_add_button(&scene_4, 0, 0, 132, 512, BLANK, true, 3, scene_4_on_button_0_pressed);
    scene_add_button(&scene_4, 380, 0, 132, 512, BLANK, true, 2, scene_4_on_button_1_pressed);
}
void scene_4_free(void)
{
    scene_free(&scene_4);
}
void scene_4_reset(void)
{
    scene_4_free();
    scene_4_init();
}

void scene_4_enter(void)
{

}
void scene_4_exit(void)
{

}

void scene_4_update(float delta)
{
    scene_translate_elapsed_time(&scene_4, delta);

    current_mouse_cursor_index = 0;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        for (int i = 0; i < scene_get_buttons_count(&scene_4); ++i)
        {
            struct button * button = scene_get_button(&scene_4, i);

            if (!button_get_is_enabled(button))
                continue;

            int x = button_get_x(button);
            int y = button_get_y(button);
            int width = button_get_width(button);
            int height = button_get_height(button);

            if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
            {
                current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    button_get_on_pressed(button)();
                }
                break;
            }
        }
    }
}
void scene_4_draw(void)
{
    DrawTexture(scene_get_background_texture(&scene_4), 0, 0, WHITE);

    for (int i = 0; i < scene_get_buttons_count(&scene_4); ++i)
    {
        struct button * button = scene_get_button(&scene_4, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }
}

void scene_4_on_button_0_pressed(void)
{
    set_scene(3);
}
void scene_4_on_button_1_pressed(void)
{
    set_scene(1);
}

/* -------- scene_4 -------- */



/* -------- scene_5 -------- */

void scene_5_init(void)
{
    scene_5 = scene_create(LoadTexture("resources/scene_5_background.png"));
    scene_init(&scene_5);

    scene_add_button(&scene_5, 322, 280, 48, 74, BLANK, true, 1, scene_5_on_button_0_pressed);
    scene_add_button(&scene_5, 0, 0, 380, 512, BLANK, true, 0, scene_5_on_button_1_pressed);
    scene_add_button(&scene_5, 380, 0, 132, 512, BLANK, true, 2, scene_5_on_button_2_pressed);

    scene_5_sprite_lever_up = sprite_create(322, 280, LoadTexture("resources/scene_5_lever_up.png"), WHITE, true);
}
void scene_5_free(void)
{
    scene_free(&scene_5);

    sprite_free(&scene_5_sprite_lever_up);
}
void scene_5_reset(void)
{
    scene_5_free();
    scene_5_init();
}

void scene_5_enter(void)
{
    sprite_set_is_visible(&scene_5_sprite_lever_up, scene_5_is_lever_up);
}
void scene_5_exit(void)
{

}

void scene_5_update(float delta)
{
    scene_translate_elapsed_time(&scene_5, delta);

    current_mouse_cursor_index = 0;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        for (int i = 0; i < scene_get_buttons_count(&scene_5); ++i)
        {
            struct button * button = scene_get_button(&scene_5, i);

            if (!button_get_is_enabled(button))
                continue;

            int x = button_get_x(button);
            int y = button_get_y(button);
            int width = button_get_width(button);
            int height = button_get_height(button);

            if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
            {
                current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    button_get_on_pressed(button)();
                }
                break;
            }
        }
    }
}
void scene_5_draw(void)
{
    DrawTexture(scene_get_background_texture(&scene_5), 0, 0, WHITE);

    sprite_draw(&scene_5_sprite_lever_up);

    for (int i = 0; i < scene_get_buttons_count(&scene_5); ++i)
    {
        struct button * button = scene_get_button(&scene_5, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }
}

void scene_5_on_button_0_pressed(void)
{
    scene_5_is_lever_up = !scene_5_is_lever_up;
    sprite_set_is_visible(&scene_5_sprite_lever_up, scene_5_is_lever_up);
}
void scene_5_on_button_1_pressed(void)
{
}
void scene_5_on_button_2_pressed(void)
{
    set_scene(6);
}

/* -------- scene_5 -------- */



/* -------- scene_6 -------- */

void scene_6_init(void)
{
    scene_6 = scene_create(LoadTexture("resources/scene_6_background.png"));
    scene_init(&scene_6);

    scene_add_button(&scene_6, 0, 0, 132, 512, BLANK, true, 3, scene_6_on_button_0_pressed);
    scene_add_button(&scene_6, 132, 0, 248, 512, BLANK, true, 0, scene_6_on_button_1_pressed);
    scene_add_button(&scene_6, 380, 0, 132, 512, BLANK, true, 2, scene_6_on_button_2_pressed);
}
void scene_6_free(void)
{
    scene_free(&scene_6);
}
void scene_6_reset(void)
{
    scene_6_free();
    scene_6_init();
}

void scene_6_enter(void)
{

}
void scene_6_exit(void)
{

}

void scene_6_update(float delta)
{
    scene_translate_elapsed_time(&scene_6, delta);

    current_mouse_cursor_index = 0;

    if (is_mouse_input_enabled)
    {
        Vector2 mouse_position = GetMousePosition();

        for (int i = 0; i < scene_get_buttons_count(&scene_6); ++i)
        {
            struct button * button = scene_get_button(&scene_6, i);

            if (!button_get_is_enabled(button))
                continue;

            int x = button_get_x(button);
            int y = button_get_y(button);
            int width = button_get_width(button);
            int height = button_get_height(button);

            if (mouse_position.x >= x && mouse_position.x < x + width && mouse_position.y >= y && mouse_position.y < y + height)
            {
                current_mouse_cursor_index = button_get_mouse_cursor_index(button);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    button_get_on_pressed(button)();
                }
                break;
            }
        }
    }
}
void scene_6_draw(void)
{
    DrawTexture(scene_get_background_texture(&scene_6), 0, 0, WHITE);

    for (int i = 0; i < scene_get_buttons_count(&scene_6); ++i)
    {
        struct button * button = scene_get_button(&scene_6, i);
        Color color = button_get_is_enabled(button) ? button_get_color(button) : GRAY;
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), color);
    }
}

void scene_6_on_button_0_pressed(void)
{
    set_scene(5);
}
void scene_6_on_button_1_pressed(void)
{
    set_scene(3);
}
void scene_6_on_button_2_pressed(void)
{
    set_scene(5);
}

/* -------- scene_6 -------- */
