#include <stdio.h>
#include "scene_0000.h"
#include "scene.h"
#include "game_data.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static struct game_data * game_data;
static void(*set_scene)(int index);

static struct sprite * sprite_background;

static struct sprite * sprite_new_game_over;
static struct sprite * sprite_load_game_over;
static struct sprite * sprite_quit_over;
static struct sprite * sprite_options_over;

static struct button * button_new_game;
static struct button * button_load_game;
static struct button * button_quit;
static struct button * button_options;

void scene_0000_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    game_data = game_data_ptr;
    set_scene = set_scene_ptr;
}
void scene_0000_free(void)
{
    scene = NULL;
    game_data = NULL;
    set_scene = NULL;
}

void scene_0000_load(void)
{
    scene_add_sprite(scene, 0, 0, "resources/scene_0000/background.png", WHITE, true);

    scene_add_sprite(scene, 446, 249, "resources/scene_0000/new_game_over.png", WHITE, false);
    scene_add_sprite(scene, 439, 266, "resources/scene_0000/load_game_over.png", WHITE, false);
    scene_add_sprite(scene, 493, 317, "resources/scene_0000/quit_over.png", WHITE, false);
    scene_add_sprite(scene, 10, 310, "resources/scene_0000/options_over.png", WHITE, false);

    scene_add_button(scene, 446, 249, 87, 12, BLANK, true, 1,
        NULL, NULL, on_released_button_new_game);

    scene_add_button(scene, 439, 266, 94, 12, BLANK, true, 1,
        NULL, NULL, NULL);

    scene_add_button(scene, 493, 317, 41, 13, BLANK, true, 1,
        NULL, NULL, on_released_button_quit);

    scene_add_button(scene, 10, 310, 74, 12, BLANK, true, 1,
        NULL, NULL, NULL);
}
void scene_0000_unload(void)
{

}

void scene_0000_enter(void)
{
    sprite_background = scene_get_sprite(scene, 0);

    sprite_new_game_over = scene_get_sprite(scene, 1);
    sprite_load_game_over = scene_get_sprite(scene, 2);
    sprite_quit_over = scene_get_sprite(scene, 3);
    sprite_options_over = scene_get_sprite(scene, 4);

    button_new_game = scene_get_button(scene, 0);
    button_load_game = scene_get_button(scene, 1);
    button_quit = scene_get_button(scene, 2);
    button_options = scene_get_button(scene, 3);
}
void scene_0000_exit(void)
{

}

void scene_0000_update(float delta)
{
    sprite_set_is_visible(sprite_new_game_over, button_get_is_mouse_over(button_new_game));
    sprite_set_is_visible(sprite_load_game_over, button_get_is_mouse_over(button_load_game));
    sprite_set_is_visible(sprite_quit_over, button_get_is_mouse_over(button_quit));
    sprite_set_is_visible(sprite_options_over, button_get_is_mouse_over(button_options));
}
void scene_0000_draw(void)
{

}

static void on_released_button_new_game(void)
{
    set_scene(2);
}

static void on_released_button_quit(void)
{
    set_scene(1);
}
