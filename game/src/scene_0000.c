#include "scene_0000.h"

static struct sprite * sprite_background;
static struct sprite * sprite_new_game_over;
static struct sprite * sprite_load_game_over;
static struct sprite * sprite_quit_over;
static struct sprite * sprite_options_over;

static struct button * button_new_game;
static struct button * button_load_game;
static struct button * button_quit;
static struct button * button_options;

void scene_0000_load(struct scene * scene)
{
    scene_add_sprite(scene, "background", "resources/scene_0000/background.png", 0, 0, WHITE, true);
    scene_add_sprite(scene, "new_game_over", "resources/scene_0000/new_game_over.png", 446, 249, WHITE, false);
    scene_add_sprite(scene, "load_game_over", "resources/scene_0000/load_game_over.png", 439, 266, WHITE, false);
    scene_add_sprite(scene, "quit_over", "resources/scene_0000/quit_over.png", 493, 317, WHITE, false);
    scene_add_sprite(scene, "options_over", "resources/scene_0000/options_over.png", 10, 310, WHITE, false);

    scene_add_button(scene, "new_game", 446, 249, 87, 12, BLANK, true, 1, NULL, NULL, on_released_button_new_game);
    scene_add_button(scene, "load_game", 439, 266, 94, 12, BLANK, true, 1, NULL, NULL, NULL);
    scene_add_button(scene, "quit", 493, 317, 41, 13, BLANK, true, 1, NULL, NULL, on_released_button_quit);
    scene_add_button(scene, "options", 10, 310, 74, 12, BLANK, true, 1, NULL, NULL, NULL);
}
void scene_0000_unload(struct scene * scene)
{

}

void scene_0000_enter(struct scene * scene)
{
    sprite_background = scene_get_sprite_from_name(scene, "background");
    sprite_new_game_over = scene_get_sprite_from_name(scene, "new_game_over");
    sprite_load_game_over = scene_get_sprite_from_name(scene, "load_game_over");
    sprite_quit_over = scene_get_sprite_from_name(scene, "quit_over");
    sprite_options_over = scene_get_sprite_from_name(scene, "options_over");

    button_new_game = scene_get_button_from_name(scene, "new_game");
    button_load_game = scene_get_button_from_name(scene, "load_game");
    button_quit = scene_get_button_from_name(scene, "quit");
    button_options = scene_get_button_from_name(scene, "options");
}
void scene_0000_exit(struct scene * scene)
{

}

void scene_0000_update(struct scene * scene, float delta)
{
    sprite_set_is_visible(sprite_new_game_over, button_get_is_mouse_over(button_new_game));
    sprite_set_is_visible(sprite_load_game_over, button_get_is_mouse_over(button_load_game));
    sprite_set_is_visible(sprite_quit_over, button_get_is_mouse_over(button_quit));
    sprite_set_is_visible(sprite_options_over, button_get_is_mouse_over(button_options));
}
void scene_0000_draw(struct scene * scene)
{

}

static void on_released_button_new_game(void)
{

}

static void on_released_button_quit(void)
{

}
