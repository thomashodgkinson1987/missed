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
    scene.sprite_names = array_create(1, 64);
    scene.buttons = array_create(1, sizeof(struct button));
    scene.button_names = array_create(1, 64);
    scene.sounds = array_create(1, sizeof(Sound));
    scene.sound_names = array_create(1, 64);

    return scene;
}

void scene_init(struct scene * scene)
{
    array_init(&scene->sprites);
    array_init(&scene->sprite_names);
    array_init(&scene->buttons);
    array_init(&scene->button_names);
    array_init(&scene->sounds);
    array_init(&scene->sound_names);
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

    array_free(&scene->sprite_names);
    scene->sprite_names = (struct array){ 0 };

    array_free(&scene->buttons);
    scene->buttons = (struct array){ 0 };

    array_free(&scene->button_names);
    scene->button_names = (struct array){ 0 };

    for (int i = 0; i < array_get_count(&scene->sounds); ++i)
    {
        Sound * sound = (Sound *)array_get(&scene->sounds, i);
        UnloadSound(*sound);
    }
    array_free(&scene->sounds);
    scene->sounds = (struct array){ 0 };

    array_free(&scene->sound_names);
    scene->sound_names = (struct array){ 0 };
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



void scene_add_sprite(struct scene * scene, char * name, int x, int y, char * texture_filename, Color tint, bool is_visible)
{
    struct sprite sprite = sprite_create(x, y, texture_filename, tint, is_visible);
    sprite_init(&sprite);
    array_append(&scene->sprites, &sprite);

    char name_buffer[64];
    strcpy(name_buffer, name);

    array_append(&scene->sprite_names, name_buffer);
}

struct sprite * scene_get_sprite_from_index(struct scene * scene, size_t index)
{
    return (struct sprite *)array_get(&scene->sprites, index);
}

struct sprite * scene_get_sprite_from_name(struct scene * scene, char * name)
{
    for (int i = 0; i < array_get_count(&scene->sprite_names); ++i)
    {
        if (strcmp(name, (char *)array_get(&scene->sprite_names, i)) == 0)
        {
            return (struct sprite *)array_get(&scene->sprites, i);
        }
    }
}

size_t scene_get_sprites_count(struct scene * scene)
{
    return array_get_count(&scene->sprites);
}



void scene_add_button(struct scene * scene, char * name, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index,
    void(*on_pressed)(void), void(*on_down)(void), void(*on_released)(void))
{
    struct button button = button_create(x, y, width, height, color, is_enabled, mouse_cursor_index, on_pressed, on_down, on_released);
    array_append(&scene->buttons, &button);

    char name_buffer[64];
    strcpy(name_buffer, name);

    array_append(&scene->button_names, name_buffer);
}

struct button * scene_get_button_from_index(struct scene * scene, size_t index)
{
    return (struct button *)array_get(&scene->buttons, index);
}

struct button * scene_get_button_from_name(struct scene * scene, char * name)
{
    for (int i = 0; i < array_get_count(&scene->button_names); ++i)
    {
        if (strcmp(name, (char *)array_get(&scene->button_names, i)) == 0)
        {
            return (struct button *)array_get(&scene->buttons, i);
        }
    }
}

size_t scene_get_buttons_count(struct scene * scene)
{
    return array_get_count(&scene->buttons);
}



void scene_add_sound(struct scene * scene, char * name, char * sound_filename)
{
    Sound sound = LoadSound(sound_filename);
    array_append(&scene->sounds, &sound);

    char name_buffer[64];
    strcpy(name_buffer, name);

    array_append(&scene->sound_names, name_buffer);
}

Sound * scene_get_sound_from_index(struct scene * scene, size_t index)
{
    return (Sound *)array_get(&scene->sounds, index);
}

Sound * scene_get_sound_from_name(struct scene * scene, char * name)
{
    for (int i = 0; i < array_get_count(&scene->sound_names); ++i)
    {
        if (strcmp(name, (char *)array_get(&scene->sound_names, i)) == 0)
        {
            return (Sound *)array_get(&scene->sounds, i);
        }
    }
}

size_t scene_get_sounds_count(struct scene * scene)
{
    return array_get_count(&scene->sounds);
}
