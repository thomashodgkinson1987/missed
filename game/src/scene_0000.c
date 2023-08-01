#include "scene_0000.h"
#include "scene.h"

static struct scene * scene;
static void(*set_scene)(int index);

static struct button * button_exit;

static struct sprite * sprite_background;

void scene_0000_init(struct scene * scene_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    set_scene = set_scene_ptr;
}
void scene_0000_free(void)
{
    scene = NULL;
    set_scene = NULL;
}

void scene_0000_load(void)
{
    scene_add_button(scene, 312, 70, 129, 89, BLANK, true, 4, NULL, NULL, on_released_button_exit);

    scene_add_sprite(scene, 0, 0, "resources/scene_0000/background.png", WHITE, true);
}
void scene_0000_unload(void)
{

}

void scene_0000_enter(void)
{
    button_exit = scene_get_button(&scene, 0);

    sprite_background = scene_get_sprite(&scene, 0);
}
void scene_0000_exit(void)
{
    button_exit = NULL;

    sprite_background = NULL;
}

void scene_0000_update(float delta)
{

}
void scene_0000_draw(void)
{

}

static void on_released_button_exit(void)
{
    set_scene(1);
}
