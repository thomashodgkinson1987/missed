#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "array.h"
#include "button.h"
#include "sprite.h"
#include "scene.h"
#include "game_data.h"



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
enum scene_transision_enum scene_transision_state;
float scene_transition_fade_out_time;
float scene_transition_wait_time;
float scene_transition_fade_in_time;
float scene_transition_timer;
Color scene_transition_color;

bool is_draw_debug;

struct scene scene;
void(*function_pointers_scene_init[7])(void);
void(*function_pointers_scene_free[7])(void);
void(*function_pointers_scene_enter[7])(void);
void(*function_pointers_scene_exit[7])(void);
void(*function_pointers_scene_update[7])(float delta);
void(*function_pointers_scene_draw[7])(void);



void game_init(void);
void game_free(void);
void game_reset(void);

void game_update(float delta);
void game_draw(void);



void set_scene(int index);



/* -------- scene_0 -------- */

struct sprite * scene_0_sprite_background;

struct button * scene_0_button_exit;

void scene_0_init(void);
void scene_0_free(void);

void scene_0_enter(void);
void scene_0_exit(void);

void scene_0_update(float delta);
void scene_0_draw(void);

void scene_0_on_button_0_pressed(void);

/* -------- scene_0 -------- */



/* -------- scene_1 -------- */

struct sprite * scene_1_sprite_background;

struct button * scene_1_button_exit_0;
struct button * scene_1_button_exit_1;
struct button * scene_1_button_exit_2;

void scene_1_init(void);
void scene_1_free(void);

void scene_1_enter(void);
void scene_1_exit(void);

void scene_1_update(float delta);
void scene_1_draw(void);

void scene_1_on_button_0_pressed(void);
void scene_1_on_button_1_pressed(void);
void scene_1_on_button_2_pressed(void);

/* -------- scene_1 -------- */



/* -------- scene_2 -------- */

struct sprite * scene_2_sprite_background;

struct button * scene_2_button_exit_0;
struct button * scene_2_button_exit_1;

void scene_2_init(void);
void scene_2_free(void);

void scene_2_enter(void);
void scene_2_exit(void);

void scene_2_update(float delta);
void scene_2_draw(void);

void scene_2_on_button_0_pressed(void);
void scene_2_on_button_1_pressed(void);

/* -------- scene_2 -------- */



/* -------- scene_3 -------- */

struct sprite * scene_3_sprite_background;

struct button * scene_3_button_exit_0;
struct button * scene_3_button_exit_1;

void scene_3_init(void);
void scene_3_free(void);

void scene_3_enter(void);
void scene_3_exit(void);

void scene_3_update(float delta);
void scene_3_draw(void);

void scene_3_on_button_0_pressed(void);
void scene_3_on_button_1_pressed(void);

/* -------- scene_3 -------- */



/* -------- scene_4 -------- */

struct sprite * scene_4_sprite_background;

struct button * scene_4_button_exit_0;
struct button * scene_4_button_exit_1;

void scene_4_init(void);
void scene_4_free(void);

void scene_4_enter(void);
void scene_4_exit(void);

void scene_4_update(float delta);
void scene_4_draw(void);

void scene_4_on_button_0_pressed(void);
void scene_4_on_button_1_pressed(void);

/* -------- scene_4 -------- */



/* -------- scene_5 -------- */

struct sprite * scene_5_sprite_background;
struct sprite * scene_5_sprite_lever_down;
struct sprite * scene_5_sprite_lever_up;

struct button * scene_5_button_lever;
struct button * scene_5_button_exit_0;
struct button * scene_5_button_exit_1;

bool scene_5_is_lever_down;

void scene_5_init(void);
void scene_5_free(void);

void scene_5_enter(void);
void scene_5_exit(void);

void scene_5_update(float delta);
void scene_5_draw(void);

void scene_5_on_button_0_pressed(void);
void scene_5_on_button_1_pressed(void);
void scene_5_on_button_2_pressed(void);

/* -------- scene_5 -------- */



/* -------- scene_6 -------- */

struct sprite * scene_6_sprite_background;

struct button * scene_6_button_exit_0;
struct button * scene_6_button_exit_1;
struct button * scene_6_button_exit_2;

void scene_6_init(void);
void scene_6_free(void);

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
    InitWindow(544, 332, "Missed");
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

    game_data = game_data_create();
    game_data_init(&game_data);

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

    scene = (struct scene){ 0 };

    function_pointers_scene_init[0] = scene_0_init;
    function_pointers_scene_init[1] = scene_1_init;
    function_pointers_scene_init[2] = scene_2_init;
    function_pointers_scene_init[3] = scene_3_init;
    function_pointers_scene_init[4] = scene_4_init;
    function_pointers_scene_init[5] = scene_5_init;
    function_pointers_scene_init[6] = scene_6_init;

    function_pointers_scene_free[0] = scene_0_free;
    function_pointers_scene_free[1] = scene_1_free;
    function_pointers_scene_free[2] = scene_2_free;
    function_pointers_scene_free[3] = scene_3_free;
    function_pointers_scene_free[4] = scene_4_free;
    function_pointers_scene_free[5] = scene_5_free;
    function_pointers_scene_free[6] = scene_6_free;

    function_pointers_scene_enter[0] = scene_0_enter;
    function_pointers_scene_enter[1] = scene_1_enter;
    function_pointers_scene_enter[2] = scene_2_enter;
    function_pointers_scene_enter[3] = scene_3_enter;
    function_pointers_scene_enter[4] = scene_4_enter;
    function_pointers_scene_enter[5] = scene_5_enter;
    function_pointers_scene_enter[6] = scene_6_enter;

    function_pointers_scene_exit[0] = scene_0_exit;
    function_pointers_scene_exit[1] = scene_1_exit;
    function_pointers_scene_exit[2] = scene_2_exit;
    function_pointers_scene_exit[3] = scene_3_exit;
    function_pointers_scene_exit[4] = scene_4_exit;
    function_pointers_scene_exit[5] = scene_5_exit;
    function_pointers_scene_exit[6] = scene_6_exit;

    function_pointers_scene_update[0] = scene_0_update;
    function_pointers_scene_update[1] = scene_1_update;
    function_pointers_scene_update[2] = scene_2_update;
    function_pointers_scene_update[3] = scene_3_update;
    function_pointers_scene_update[4] = scene_4_update;
    function_pointers_scene_update[5] = scene_5_update;
    function_pointers_scene_update[6] = scene_6_update;

    function_pointers_scene_draw[0] = scene_0_draw;
    function_pointers_scene_draw[1] = scene_1_draw;
    function_pointers_scene_draw[2] = scene_2_draw;
    function_pointers_scene_draw[3] = scene_3_draw;
    function_pointers_scene_draw[4] = scene_4_draw;
    function_pointers_scene_draw[5] = scene_5_draw;
    function_pointers_scene_draw[6] = scene_6_draw;

    is_draw_debug = true;
}
void game_free(void)
{
    printf("game_free\n");

    if (current_scene_index != -1)
    {
        function_pointers_scene_free[current_scene_index]();
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
    scene_transision_state = SCENE_TRANSITION_IDLE;
    scene_transition_fade_out_time = 0.0f;
    scene_transition_wait_time = 0.0f;
    scene_transition_fade_in_time = 0.0f;
    scene_transition_timer = 0.0f;
    scene_transition_color = BLANK;

    scene = (struct scene){ 0 };

    function_pointers_scene_init[0] = NULL;
    function_pointers_scene_init[1] = NULL;
    function_pointers_scene_init[2] = NULL;
    function_pointers_scene_init[3] = NULL;
    function_pointers_scene_init[4] = NULL;
    function_pointers_scene_init[5] = NULL;
    function_pointers_scene_init[6] = NULL;

    function_pointers_scene_free[0] = NULL;
    function_pointers_scene_free[1] = NULL;
    function_pointers_scene_free[2] = NULL;
    function_pointers_scene_free[3] = NULL;
    function_pointers_scene_free[4] = NULL;
    function_pointers_scene_free[5] = NULL;
    function_pointers_scene_free[6] = NULL;

    function_pointers_scene_enter[0] = NULL;
    function_pointers_scene_enter[1] = NULL;
    function_pointers_scene_enter[2] = NULL;
    function_pointers_scene_enter[3] = NULL;
    function_pointers_scene_enter[4] = NULL;
    function_pointers_scene_enter[5] = NULL;
    function_pointers_scene_enter[6] = NULL;

    function_pointers_scene_exit[0] = NULL;
    function_pointers_scene_exit[1] = NULL;
    function_pointers_scene_exit[2] = NULL;
    function_pointers_scene_exit[3] = NULL;
    function_pointers_scene_exit[4] = NULL;
    function_pointers_scene_exit[5] = NULL;
    function_pointers_scene_exit[6] = NULL;

    function_pointers_scene_update[0] = NULL;
    function_pointers_scene_update[1] = NULL;
    function_pointers_scene_update[2] = NULL;
    function_pointers_scene_update[3] = NULL;
    function_pointers_scene_update[4] = NULL;
    function_pointers_scene_update[5] = NULL;
    function_pointers_scene_update[6] = NULL;

    function_pointers_scene_draw[0] = NULL;
    function_pointers_scene_draw[1] = NULL;
    function_pointers_scene_draw[2] = NULL;
    function_pointers_scene_draw[3] = NULL;
    function_pointers_scene_draw[4] = NULL;
    function_pointers_scene_draw[5] = NULL;
    function_pointers_scene_draw[6] = NULL;

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
                function_pointers_scene_exit[current_scene_index]();
                function_pointers_scene_free[current_scene_index]();
                scene_free(&scene);
                scene = (struct scene){ 0 };
            }
            current_scene_index = next_scene_index;
            next_scene_index = -1;
            if (current_scene_index != -1)
            {
                scene = scene_create();
                scene_init(&scene);
                function_pointers_scene_init[current_scene_index]();
                function_pointers_scene_enter[current_scene_index]();
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
        scene_translate_elapsed_time(&scene, delta);

        current_mouse_cursor_index = 0;

        if (is_mouse_input_enabled)
        {
            Vector2 mouse_position = GetMousePosition();

            for (int i = 0; i < scene_get_buttons_count(&scene); ++i)
            {
                struct button * button = scene_get_button(&scene, i);

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

        function_pointers_scene_update[current_scene_index](delta);
    }
}
void game_draw(void)
{
    BeginDrawing();

    ClearBackground(WHITE);

    if (current_scene_index != -1)
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

        function_pointers_scene_draw[current_scene_index]();
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
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), scene_transition_color);
    }

    if (is_draw_debug)
    {
        DrawRectangle(0, 0, 138, 26, BLACK);
        DrawText(TextFormat("current_scene_index: %d", current_scene_index), 8, 8, 8, WHITE);
    }

    EndDrawing();
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
    scene_0_sprite_background = scene_add_sprite(&scene, 0, 0, "resources/scene_0/background.png", WHITE, true);

    scene_0_button_exit = scene_add_button(&scene, 312, 70, 129, 89, BLANK, true, 1, scene_0_on_button_0_pressed);
}
void scene_0_free(void)
{
    scene_0_sprite_background = NULL;

    scene_0_button_exit = NULL;
}

void scene_0_enter(void)
{

}
void scene_0_exit(void)
{

}

void scene_0_update(float delta)
{

}
void scene_0_draw(void)
{

}

void scene_0_on_button_0_pressed(void)
{
    set_scene(1);
}

/* -------- scene_0 -------- */



/* -------- scene_1 -------- */

void scene_1_init(void)
{
    scene_1_sprite_background = scene_add_sprite(&scene, 0, 0, "resources/scene_1/background.png", WHITE, true);

    scene_1_button_exit_0 = scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 3, scene_1_on_button_0_pressed);
    scene_1_button_exit_1 = scene_add_button(&scene, 142, 0, 260, 332, BLANK, true, 0, scene_1_on_button_1_pressed);
    scene_1_button_exit_2 = scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2, scene_1_on_button_2_pressed);
}
void scene_1_free(void)
{
    scene_1_sprite_background = NULL;

    scene_1_button_exit_0 = NULL;
    scene_1_button_exit_1 = NULL;
    scene_1_button_exit_2 = NULL;
}

void scene_1_enter(void)
{

}
void scene_1_exit(void)
{

}

void scene_1_update(float delta)
{

}
void scene_1_draw(void)
{

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
    scene_2_sprite_background = scene_add_sprite(&scene, 0, 0, "resources/scene_2/background.png", WHITE, true);

    scene_2_button_exit_0 = scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 3, scene_2_on_button_0_pressed);
    scene_2_button_exit_1 = scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2, scene_2_on_button_1_pressed);
}
void scene_2_free(void)
{
    scene_2_sprite_background = NULL;

    scene_2_button_exit_0 = NULL;
    scene_2_button_exit_1 = NULL;
}

void scene_2_enter(void)
{

}
void scene_2_exit(void)
{

}

void scene_2_update(float delta)
{

}
void scene_2_draw(void)
{

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
    scene_3_sprite_background = scene_add_sprite(&scene, 0, 0, "resources/scene_3/background.png", WHITE, true);

    scene_3_button_exit_0 = scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 3, scene_3_on_button_0_pressed);
    scene_3_button_exit_1 = scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2, scene_3_on_button_1_pressed);
}
void scene_3_free(void)
{
    scene_3_sprite_background = NULL;

    scene_3_button_exit_0 = NULL;
    scene_3_button_exit_1 = NULL;
}

void scene_3_enter(void)
{

}
void scene_3_exit(void)
{

}

void scene_3_update(float delta)
{

}
void scene_3_draw(void)
{

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
    scene_4_sprite_background = scene_add_sprite(&scene, 0, 0, "resources/scene_4/background.png", WHITE, true);

    scene_4_button_exit_0 = scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 3, scene_4_on_button_0_pressed);
    scene_4_button_exit_1 = scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2, scene_4_on_button_1_pressed);
}
void scene_4_free(void)
{
    scene_4_sprite_background = NULL;

    scene_4_button_exit_0 = NULL;
    scene_4_button_exit_1 = NULL;
}

void scene_4_enter(void)
{

}
void scene_4_exit(void)
{

}

void scene_4_update(float delta)
{

}
void scene_4_draw(void)
{

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
    scene_5_sprite_background = scene_add_sprite(&scene, 0, 0, "resources/scene_5/background.png", WHITE, true);
    scene_5_sprite_lever_down = scene_add_sprite(&scene, 352, 183, "resources/scene_5/lever_down.png", WHITE, true);
    scene_5_sprite_lever_up = scene_add_sprite(&scene, 352, 183, "resources/scene_5/lever_up.png", WHITE, true);

    scene_5_button_lever = scene_add_button(&scene, 352, 183, 39, 41, BLANK, true, 1, scene_5_on_button_0_pressed);
    scene_5_button_exit_0 = scene_add_button(&scene, 0, 0, 402, 332, BLANK, true, 0, scene_5_on_button_1_pressed);
    scene_5_button_exit_1 = scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2, scene_5_on_button_2_pressed);

    scene_5_is_lever_down = true;

    if (!game_data_has_bool(&game_data, "scene_5_is_lever_down"))
    {
        game_data_add_bool(&game_data, "scene_5_is_lever_down", scene_5_is_lever_down);
    }
    else
    {
        scene_5_is_lever_down = game_data_get_bool(&game_data, "scene_5_is_lever_down");
    }
}
void scene_5_free(void)
{
    scene_5_sprite_background = NULL;
    scene_5_sprite_lever_down = NULL;
    scene_5_sprite_lever_up = NULL;

    scene_5_button_lever = NULL;
    scene_5_button_exit_0 = NULL;
    scene_5_button_exit_1 = NULL;

    scene_5_is_lever_down = false;
}

void scene_5_enter(void)
{
    sprite_set_is_visible(scene_5_sprite_lever_down, scene_5_is_lever_down);
    sprite_set_is_visible(scene_5_sprite_lever_up, !scene_5_is_lever_down);
}
void scene_5_exit(void)
{

}

void scene_5_update(float delta)
{

}
void scene_5_draw(void)
{

}

void scene_5_on_button_0_pressed(void)
{
    scene_5_is_lever_down = !scene_5_is_lever_down;
    game_data_set_bool(&game_data, "scene_5_is_lever_down", scene_5_is_lever_down);

    sprite_set_is_visible(scene_5_sprite_lever_down, scene_5_is_lever_down);
    sprite_set_is_visible(scene_5_sprite_lever_up, !scene_5_is_lever_down);
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
    scene_6_sprite_background = scene_add_sprite(&scene, 0, 0, "resources/scene_6/background.png", WHITE, true);

    scene_6_button_exit_0 = scene_add_button(&scene, 0, 0, 142, 332, BLANK, true, 3, scene_6_on_button_0_pressed);
    scene_6_button_exit_1 = scene_add_button(&scene, 142, 0, 402, 332, BLANK, true, 0, scene_6_on_button_1_pressed);
    scene_6_button_exit_2 = scene_add_button(&scene, 402, 0, 142, 332, BLANK, true, 2, scene_6_on_button_2_pressed);
}
void scene_6_free(void)
{
    scene_6_sprite_background = NULL;

    scene_6_button_exit_0 = NULL;
    scene_6_button_exit_1 = NULL;
    scene_6_button_exit_2 = NULL;
}

void scene_6_enter(void)
{

}
void scene_6_exit(void)
{

}

void scene_6_update(float delta)
{

}
void scene_6_draw(void)
{

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
