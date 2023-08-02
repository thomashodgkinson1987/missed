#include <string.h>
#include "raylib.h"
#include "scene.h"
#include "array.h"
#include "sprite.h"
#include "button.h"



struct scene scene_create(void)
{
    struct scene scene = (struct scene){ 0 };

    scene.elapsed_time = 0.0f;
    scene.sprites = array_create(1, sizeof(struct sprite));
    scene.buttons = array_create(1, sizeof(struct button));
    scene.sounds = array_create(1, sizeof(Sound));

    return scene;
}

void scene_init(struct scene * scene)
{
    array_init(&scene->sprites);
    array_init(&scene->buttons);
    array_init(&scene->sounds);
}

void scene_free(struct scene * scene)
{
    scene->elapsed_time = 0.0f;

    for (int i = 0; i < array_get_count(&scene->sprites); ++i)
    {
        struct sprite * sprite = (struct sprite *)array_get(&scene->sprites, i);
        sprite_free(sprite);
    }
    array_free(&scene->sprites);
    scene->sprites = (struct array){ 0 };

    array_free(&scene->buttons);
    scene->buttons = (struct array){ 0 };

    for (int i = 0; i < array_get_count(&scene->sounds); ++i)
    {
        Sound * sound = (Sound *)array_get(&scene->sounds, i);
        UnloadSound(*sound);
    }
    array_free(&scene->sounds);
    scene->sounds = (struct array){ 0 };
}

void scene_reset(struct scene * scene)
{
    scene_free(scene);
    *scene = scene_create();
    scene_init(scene);
}



float scene_get_elapsed_time(struct scene * scene)
{
    return scene->elapsed_time;
}



void scene_set_elapsed_time(struct scene * scene, float elapsed_time)
{
    scene->elapsed_time = elapsed_time;
}



void scene_translate_elapsed_time(struct scene * scene, float delapsed_time)
{
    scene->elapsed_time += delapsed_time;
}



void scene_add_sprite(struct scene * scene, int x, int y, char * texture_filename, Color tint, bool is_visible)
{
    struct sprite sprite = sprite_create(x, y, texture_filename, tint, is_visible);
    sprite_init(&sprite);
    array_append(&scene->sprites, &sprite);
}

struct sprite * scene_get_sprite(struct scene * scene, size_t index)
{
    return (struct sprite *)array_get(&scene->sprites, index);
}

size_t scene_get_sprites_count(struct scene * scene)
{
    return array_get_count(&scene->sprites);
}



void scene_add_button(struct scene * scene, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index,
    void(*on_pressed)(void), void(*on_down)(void), void(*on_released)(void))
{
    struct button button = button_create(x, y, width, height, color, is_enabled, mouse_cursor_index, on_pressed, on_down, on_released);
    array_append(&scene->buttons, &button);
}

struct button * scene_get_button(struct scene * scene, size_t index)
{
    return (struct button *)array_get(&scene->buttons, index);
}

size_t scene_get_buttons_count(struct scene * scene)
{
    return array_get_count(&scene->buttons);
}



void scene_add_sound(struct scene * scene, char * sound_filename)
{
    Sound sound = LoadSound(sound_filename);
    array_append(&scene->sounds, &sound);
}

Sound * scene_get_sound(struct scene * scene, size_t index)
{
    return (Sound *)array_get(&scene->sounds, index);
}

size_t scene_get_sounds_count(struct scene * scene)
{
    return array_get_count(&scene->sounds);
}
