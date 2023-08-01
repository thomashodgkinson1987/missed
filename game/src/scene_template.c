#include "scene_template.h"
#include "scene.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static void(*set_scene)(int index);

void scene_template_init(struct scene * scene_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    set_scene = set_scene_ptr;
}
void scene_template_free(void)
{
    scene = NULL;
    set_scene = NULL;
}

void scene_template_load(void)
{

}
void scene_template_unload(void)
{

}

void scene_template_enter(void)
{

}
void scene_template_exit(void)
{

}

void scene_template_update(float delta)
{

}
void scene_template_draw(void)
{

}
