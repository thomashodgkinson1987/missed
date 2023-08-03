#include "scene_0000.h"
#include "scene.h"
#include "scene_function_pointers.h"
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

static void scene_0000_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    game_data = game_data_ptr;
    set_scene = set_scene_ptr;
}
static void scene_0000_free(void)
{
    scene = NULL;
    game_data = NULL;
    set_scene = NULL;
}

static void scene_0000_load(void)
{
    scene_add_sprite(scene, "background", 0, 0, "resources/scene_0000/background.png", WHITE, true);

    scene_add_sprite(scene, "new_game_over", 446, 249, "resources/scene_0000/new_game_over.png", WHITE, false);
    scene_add_sprite(scene, "load_game_over", 439, 266, "resources/scene_0000/load_game_over.png", WHITE, false);
    scene_add_sprite(scene, "quit_over", 493, 317, "resources/scene_0000/quit_over.png", WHITE, false);
    scene_add_sprite(scene, "options_over", 10, 310, "resources/scene_0000/options_over.png", WHITE, false);

    scene_add_button(scene, "new_game", 446, 249, 87, 12, BLANK, true, 1, NULL, NULL, on_released_button_new_game);
    scene_add_button(scene, "load_game", 439, 266, 94, 12, BLANK, true, 1, NULL, NULL, NULL);
    scene_add_button(scene, "quit", 493, 317, 41, 13, BLANK, true, 1, NULL, NULL, on_released_button_quit);
    scene_add_button(scene, "options", 10, 310, 74, 12, BLANK, true, 1, NULL, NULL, NULL);
}
static void scene_0000_unload(void)
{

}

static void scene_0000_enter(void)
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
static void scene_0000_exit(void)
{

}

static void scene_0000_update(float delta)
{
    sprite_set_is_visible(sprite_new_game_over, button_get_is_mouse_over(button_new_game));
    sprite_set_is_visible(sprite_load_game_over, button_get_is_mouse_over(button_load_game));
    sprite_set_is_visible(sprite_quit_over, button_get_is_mouse_over(button_quit));
    sprite_set_is_visible(sprite_options_over, button_get_is_mouse_over(button_options));
}
static void scene_0000_draw(void)
{

}

struct scene_function_pointers scene_0000_get_function_pointers(void)
{
    return scene_function_pointers_create(
        scene_0000_init,
        scene_0000_free,
        scene_0000_load,
        scene_0000_unload,
        scene_0000_enter,
        scene_0000_exit,
        scene_0000_update,
        scene_0000_draw
    );
}

static void on_released_button_new_game(void)
{
    set_scene(2);
}

static void on_released_button_quit(void)
{
    set_scene(1);
}
