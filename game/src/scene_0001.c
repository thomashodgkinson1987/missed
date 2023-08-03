#include "scene_0001.h"
#include "scene.h"
#include "scene_function_pointers.h"
#include "game_data.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static struct game_data * game_data;
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

static void scene_0001_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    game_data = game_data_ptr;
    set_scene = set_scene_ptr;
}
static void scene_0001_free(void)
{
    scene = NULL;
    game_data = NULL;
    set_scene = NULL;
}

static void scene_0001_load(void)
{
    scene_add_sprite(scene, "slide_0", 0, 0, "resources/scene_0001/slide_0.png", WHITE, true);
    scene_add_sprite(scene, "slide_1", 0, 0, "resources/scene_0001/slide_1.png", WHITE, false);
    scene_add_sprite(scene, "slide_2", 0, 0, "resources/scene_0001/slide_2.png", WHITE, false);
    scene_add_sprite(scene, "slide_3", 0, 0, "resources/scene_0001/slide_3.png", WHITE, false);
    scene_add_sprite(scene, "slide_4", 0, 0, "resources/scene_0001/slide_4.png", WHITE, false);
    scene_add_sprite(scene, "slide_5", 0, 0, "resources/scene_0001/slide_5.png", WHITE, false);
    scene_add_sprite(scene, "slide_6", 0, 0, "resources/scene_0001/slide_6.png", WHITE, false);

    scene_add_button(scene, "quit", 0, 0, 544, 332, BLANK, true, 1, NULL, NULL, on_released_button_quit);
}
static void scene_0001_unload(void)
{

}

static void scene_0001_enter(void)
{
    sprite_slide_0000 = scene_get_sprite_from_name(scene, "slide_0");
    sprite_slide_0001 = scene_get_sprite_from_name(scene, "slide_1");
    sprite_slide_0002 = scene_get_sprite_from_name(scene, "slide_2");
    sprite_slide_0003 = scene_get_sprite_from_name(scene, "slide_3");
    sprite_slide_0004 = scene_get_sprite_from_name(scene, "slide_4");
    sprite_slide_0005 = scene_get_sprite_from_name(scene, "slide_5");
    sprite_slide_0006 = scene_get_sprite_from_name(scene, "slide_6");

    button_quit = scene_get_button_from_name(scene, "quit");

    slide_time = 4.0f;
    slide_timer = 0.0f;

    slides_count = 7;

    slides[0] = sprite_slide_0000;
    slides[1] = sprite_slide_0001;
    slides[2] = sprite_slide_0002;
    slides[3] = sprite_slide_0003;
    slides[4] = sprite_slide_0004;
    slides[5] = sprite_slide_0005;
    slides[6] = sprite_slide_0006;

    current_slide_index = 0;
}
static void scene_0001_exit(void)
{

}

static void scene_0001_update(float delta)
{
    slide_timer += delta;
    if (slide_timer >= slide_time)
    {
        slide_timer = 0.0f;
        sprite_toggle_is_visible(slides[current_slide_index++]);
        if (current_slide_index < slides_count)
            sprite_toggle_is_visible(slides[current_slide_index]);
        else
            set_scene(-1);
    }
}
static void scene_0001_draw(void)
{

}

struct scene_function_pointers scene_0001_get_function_pointers(void)
{
    return scene_function_pointers_create(
        scene_0001_init,
        scene_0001_free,
        scene_0001_load,
        scene_0001_unload,
        scene_0001_enter,
        scene_0001_exit,
        scene_0001_update,
        scene_0001_draw
    );
}

static void on_released_button_quit(void)
{
    set_scene(-1);
}
