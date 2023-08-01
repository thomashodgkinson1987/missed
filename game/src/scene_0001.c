#include "scene_0001.h"
#include "scene.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static void(*set_scene)(int index);

static struct sprite * sprite_slide_0000;
static struct sprite * sprite_slide_0001;
static struct sprite * sprite_slide_0002;
static struct sprite * sprite_slide_0003;
static struct sprite * sprite_slide_0004;
static struct sprite * sprite_slide_0005;
static struct sprite * sprite_slide_0006;

static struct button * button_quit;

static float slide_time;
static float slide_timer;

static size_t slides_count;
static struct sprite * slides[7];

static size_t current_slide_index;

void scene_0001_init(struct scene * scene_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    set_scene = set_scene_ptr;
}
void scene_0001_free(void)
{
    scene = NULL;
    set_scene = NULL;
}

void scene_0001_load(void)
{
    scene_add_sprite(scene, 0, 0, "resources/scene_0001/slide_0000.png", WHITE, true);
    scene_add_sprite(scene, 0, 0, "resources/scene_0001/slide_0001.png", WHITE, false);
    scene_add_sprite(scene, 0, 0, "resources/scene_0001/slide_0002.png", WHITE, false);
    scene_add_sprite(scene, 0, 0, "resources/scene_0001/slide_0003.png", WHITE, false);
    scene_add_sprite(scene, 0, 0, "resources/scene_0001/slide_0004.png", WHITE, false);
    scene_add_sprite(scene, 0, 0, "resources/scene_0001/slide_0005.png", WHITE, false);
    scene_add_sprite(scene, 0, 0, "resources/scene_0001/slide_0006.png", WHITE, false);

    scene_add_button(scene, 0, 0, 544, 332, BLANK, true, 1,
        NULL, NULL, on_released_button_quit);

    slide_time = 5.0f;
    slide_timer = 0.0f;

    slides_count = 7;
    for (int i = 0; i < slides_count; ++i)
    {
        slides[i] = NULL;
    }

    current_slide_index = 0;
}
void scene_0001_unload(void)
{
    sprite_slide_0000 = NULL;
    sprite_slide_0001 = NULL;
    sprite_slide_0002 = NULL;
    sprite_slide_0003 = NULL;
    sprite_slide_0004 = NULL;
    sprite_slide_0005 = NULL;
    sprite_slide_0006 = NULL;

    button_quit = NULL;

    slide_time = 0.0f;
    slide_timer = 0.0f;

    for (int i = 0; i < slides_count; ++i)
    {
        slides[i] = NULL;
    }
    slides_count = 0;

    current_slide_index = 0;
}

void scene_0001_enter(void)
{
    sprite_slide_0000 = scene_get_sprite(scene, 0);
    sprite_slide_0001 = scene_get_sprite(scene, 1);
    sprite_slide_0002 = scene_get_sprite(scene, 2);
    sprite_slide_0003 = scene_get_sprite(scene, 3);
    sprite_slide_0004 = scene_get_sprite(scene, 4);
    sprite_slide_0005 = scene_get_sprite(scene, 5);
    sprite_slide_0006 = scene_get_sprite(scene, 6);

    button_quit = scene_get_button(scene, 0);

    for (int i = 0; i < slides_count; ++i)
    {
        slides[i] = scene_get_sprite(scene, i);
    }
}
void scene_0001_exit(void)
{

}

void scene_0001_update(float delta)
{

}
void scene_0001_draw(void)
{

}

static void on_released_button_quit(void)
{
    set_scene(-1);
}
