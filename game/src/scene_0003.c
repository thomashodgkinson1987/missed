#include "scene_0003.h"
#include "scene.h"
#include "scene_function_pointers.h"
#include "game_data.h"
#include "sprite.h"
#include "button.h"

static struct scene * scene;
static struct game_data * game_data;
static void(*set_scene)(int index);

static struct sprite * sprite_background;

static struct sprite * sprite_letter_floor;
static struct sprite * sprite_letter_full;

static struct button * button_letter_floor;
static struct button * button_letter_full_blocker;
static struct button * button_letter_full_close;

static void scene_0003_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index))
{
    scene = scene_ptr;
    game_data = game_data_ptr;
    set_scene = set_scene_ptr;
}
static void scene_0003_free(void)
{
    scene = NULL;
    game_data = NULL;
    set_scene = NULL;
}

static void scene_0003_load(void)
{
    scene_add_sprite(scene, "background", 0, 0, "resources/scene_0003/background.png", WHITE, true);
    scene_add_sprite(scene, "letter_floor", 392, 286, "resources/scene_0003/letter_floor.png", WHITE, true);
    scene_add_sprite(scene, "letter_full", 153, 9, "resources/scene_0003/letter_full.png", WHITE, false);

    scene_add_button(scene, "letter_floor", 392, 286, 43, 29, BLANK, true, 4, NULL, NULL, on_released_button_letter_floor);
    scene_add_button(scene, "letter_full_blocker", 153, 9, 239, 313, BLANK, false, 1, NULL, NULL, NULL);
    scene_add_button(scene, "letter_full_close", 0, 0, 544, 332, BLANK, false, 3, NULL, NULL, on_released_button_letter_full_close);
}
static void scene_0003_unload(void)
{

}

static void scene_0003_enter(void)
{
    sprite_background = scene_get_sprite_from_name(scene, "background");
    sprite_letter_floor = scene_get_sprite_from_name(scene, "letter_floor");
    sprite_letter_full = scene_get_sprite_from_name(scene, "letter_full");

    button_letter_floor = scene_get_button_from_name(scene, "letter_floor");
    button_letter_full_blocker = scene_get_button_from_name(scene, "letter_full_blocker");
    button_letter_full_close = scene_get_button_from_name(scene, "letter_full_close");
}
static void scene_0003_exit(void)
{

}

static void scene_0003_update(float delta)
{

}
static void scene_0003_draw(void)
{

}

struct scene_function_pointers scene_0003_get_function_pointers(void)
{
    return scene_function_pointers_create(
        scene_0003_init,
        scene_0003_free,
        scene_0003_load,
        scene_0003_unload,
        scene_0003_enter,
        scene_0003_exit,
        scene_0003_update,
        scene_0003_draw
    );
}

static void on_released_button_letter_floor(void)
{
    sprite_set_is_visible(sprite_letter_floor, false);
    sprite_set_is_visible(sprite_letter_full, true);

    button_set_is_enabled(button_letter_floor, false);
    button_set_is_enabled(button_letter_full_blocker, true);
    button_set_is_enabled(button_letter_full_close, true);
}

static void on_released_button_letter_full_close(void)
{
    sprite_set_is_visible(sprite_letter_floor, true);
    sprite_set_is_visible(sprite_letter_full, false);

    button_set_is_enabled(button_letter_floor, true);
    button_set_is_enabled(button_letter_full_blocker, false);
    button_set_is_enabled(button_letter_full_close, false);
}
