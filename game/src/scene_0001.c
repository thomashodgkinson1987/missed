#include "scene_0001.h"

#include "button.h"
#include "game_data.h"
#include "sprite.h"

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

void scene_0001_load   (struct scene * scene)
{
    scene_add_sprite(scene, "slide_0", "resources/scene_0001/slide_0.png", 0, 0, WHITE, true);
    scene_add_sprite(scene, "slide_1", "resources/scene_0001/slide_1.png", 0, 0, WHITE, false);
    scene_add_sprite(scene, "slide_2", "resources/scene_0001/slide_2.png", 0, 0, WHITE, false);
    scene_add_sprite(scene, "slide_3", "resources/scene_0001/slide_3.png", 0, 0, WHITE, false);
    scene_add_sprite(scene, "slide_4", "resources/scene_0001/slide_4.png", 0, 0, WHITE, false);
    scene_add_sprite(scene, "slide_5", "resources/scene_0001/slide_5.png", 0, 0, WHITE, false);
    scene_add_sprite(scene, "slide_6", "resources/scene_0001/slide_6.png", 0, 0, WHITE, false);

    scene_add_button(scene, "quit", 0, 0, 544, 332, BLANK, true, 1, NULL, NULL, on_released_button_quit);
}
void scene_0001_unload (struct scene * scene)
{

}

void scene_0001_enter  (struct scene * scene)
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
void scene_0001_exit   (struct scene * scene)
{

}

void scene_0001_update (struct scene * scene, float delta)
{
    if (current_slide_index < slides_count)
    {
        slide_timer += delta;
        if (slide_timer >= slide_time)
        {
            slide_timer = 0.0f;
            sprite_toggle_is_visible(slides[current_slide_index++]);
            if (current_slide_index < slides_count)
                sprite_toggle_is_visible(slides[current_slide_index]);
        }
    }
}
void scene_0001_draw   (struct scene * scene)
{

}

static void on_released_button_quit (void)
{

}
