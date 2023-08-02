#include "scene_0002.h"
#include "scene.h"
#include "game_data.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static struct game_data * game_data;
static void(*set_scene)(int index);

static struct sprite * sprite_background;

static struct button * button_exit;

void scene_0002_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    game_data = game_data_ptr;
    set_scene = set_scene_ptr;
}
void scene_0002_free(void)
{
    scene = NULL;
    game_data = NULL;
    set_scene = NULL;
}

void scene_0002_load(void)
{
    scene_add_sprite(scene, 0, 0, "resources/scene_0002/background.png", WHITE, true);

    scene_add_button(scene, 312, 70, 129, 89, BLANK, true, 4, NULL, NULL, on_released_button_exit);
}
void scene_0002_unload(void)
{

}

void scene_0002_enter(void)
{
    sprite_background = scene_get_sprite(scene, 0);

    button_exit = scene_get_button(scene, 0);
}
void scene_0002_exit(void)
{
    
}

void scene_0002_update(float delta)
{

}
void scene_0002_draw(void)
{

}

static void on_released_button_exit(void)
{
    set_scene(3);
}
