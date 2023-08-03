#include "scene_template.h"
#include "scene.h"
#include "scene_function_pointers.h"
#include "game_data.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static struct game_data * game_data;
static void(*set_scene)(int index);

static void scene_template_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    game_data = game_data_ptr;
    set_scene = set_scene_ptr;
}
static void scene_template_free(void)
{
    scene = NULL;
    game_data = NULL;
    set_scene = NULL;
}

static void scene_template_load(void)
{

}
static void scene_template_unload(void)
{

}

static void scene_template_enter(void)
{

}
static void scene_template_exit(void)
{

}

static void scene_template_update(float delta)
{

}
static void scene_template_draw(void)
{

}

struct scene_function_pointers scene_template_get_function_pointers(void)
{
    return scene_function_pointers_create(
        scene_template_init,
        scene_template_free,
        scene_template_load,
        scene_template_unload,
        scene_template_enter,
        scene_template_exit,
        scene_template_update,
        scene_template_draw
    );
}
