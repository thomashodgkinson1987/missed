#include "scene_0002.h"
#include "scene.h"
#include "scene_function_pointers.h"
#include "game_data.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static struct game_data * game_data;
static void(*set_scene)(int index);

static struct sprite * sprite_background;

static struct button * button_exit;

static void scene_0002_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    game_data = game_data_ptr;
    set_scene = set_scene_ptr;
}
static void scene_0002_free(void)
{
    scene = NULL;
    game_data = NULL;
    set_scene = NULL;
}

static void scene_0002_load(void)
{
    scene_add_sprite(scene, "background", 0, 0, "resources/scene_0002/background.png", WHITE, true);

    scene_add_button(scene, "exit", 312, 70, 129, 89, BLANK, true, 4, NULL, NULL, on_released_button_exit);
}
static void scene_0002_unload(void)
{

}

static void scene_0002_enter(void)
{
    sprite_background = scene_get_sprite_from_name(scene, "background");

    button_exit = scene_get_button_from_name(scene, "quit");
}
static void scene_0002_exit(void)
{

}

static void scene_0002_update(float delta)
{

}
static void scene_0002_draw(void)
{

}

struct scene_function_pointers scene_0002_get_function_pointers(void)
{
    return scene_function_pointers_create(
        scene_0002_init,
        scene_0002_free,
        scene_0002_load,
        scene_0002_unload,
        scene_0002_enter,
        scene_0002_exit,
        scene_0002_update,
        scene_0002_draw
    );
}

static void on_released_button_exit(void)
{
    set_scene(3);
}
