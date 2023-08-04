#include "scene.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>



struct scene scene_create(int id, char * name, void(*load_ptr)(struct scene * scene), void(*unload_ptr)(struct scene * scene), void(*enter_ptr)(struct scene * scene), void(*exit_ptr)(struct scene * scene), void(*update_ptr)(struct scene * scene, float delta), void(*draw_ptr)(struct scene * scene))
{
    struct scene scene = (struct scene){ 0 };

    scene.id = id;

    char * ptr = (char *)calloc(1, strlen(name) + 1);
    assert(ptr != NULL);
    strcpy(ptr, name);
    scene.name = ptr;

    scene.elapsed_time = 0.0f;

    scene.sprites = array_create(1, sizeof(struct sprite));
    scene.sprite_names = array_create(1, sizeof(char *));
    scene.buttons = array_create(1, sizeof(struct button));
    scene.button_names = array_create(1, sizeof(char *));
    scene.sounds = array_create(1, sizeof(Sound));
    scene.sound_names = array_create(1, sizeof(char *));

    scene.load = load_ptr;
    scene.unload = unload_ptr;
    scene.enter = enter_ptr;
    scene.exit = exit_ptr;
    scene.update = update_ptr;
    scene.draw = draw_ptr;

    return scene;
}

void scene_free(struct scene * scene)
{
    scene->id = 0;

    free(scene->name);
    scene->name = NULL;

    scene->elapsed_time = 0.0f;

    for (int i = 0; i < array_get_count(&scene->sprites); ++i)
    {
        struct sprite * sprite = (struct sprite *)array_get(&scene->sprites, i);
        sprite_free(sprite);
    }

    array_free(&scene->sprites);
    scene->sprites = (struct array){ 0 };

    for (int i = 0; i < array_get_count(&scene->sprite_names); ++i)
    {
        char * ptr = *(char **)array_get(&scene->sprite_names, i);
        free(ptr);
    }

    array_free(&scene->sprite_names);
    scene->sprite_names = (struct array){ 0 };

    array_free(&scene->buttons);
    scene->buttons = (struct array){ 0 };

    for (int i = 0; i < array_get_count(&scene->button_names); ++i)
    {
        char * ptr = *(char **)array_get(&scene->button_names, i);
        free(ptr);
    }

    array_free(&scene->button_names);
    scene->button_names = (struct array){ 0 };

    for (int i = 0; i < array_get_count(&scene->sounds); ++i)
    {
        Sound * sound = (Sound *)array_get(&scene->sounds, i);
        UnloadSound(*sound);
    }

    array_free(&scene->sounds);
    scene->sounds = (struct array){ 0 };

    for (int i = 0; i < array_get_count(&scene->sound_names); ++i)
    {
        char * ptr = *(char **)array_get(&scene->sound_names, i);
        free(ptr);
    }

    array_free(&scene->sound_names);
    scene->sound_names = (struct array){ 0 };

    scene->load = NULL;
    scene->unload = NULL;
    scene->enter = NULL;
    scene->exit = NULL;
    scene->update = NULL;
    scene->draw = NULL;
}

void scene_reset(struct scene * scene, int id, char * name, void(*load_ptr)(struct scene * scene), void(*unload_ptr)(struct scene * scene), void(*enter_ptr)(struct scene * scene), void(*exit_ptr)(struct scene * scene), void(*update_ptr)(struct scene * scene, float delta), void(*draw_ptr)(struct scene * scene))
{
    scene_free(scene);
    *scene = scene_create(id, name, load_ptr, unload_ptr, enter_ptr, exit_ptr, update_ptr, draw_ptr);
}



int scene_get_id(struct scene * scene)
{
    return scene->id;
}

char * scene_get_name(struct scene * scene)
{
    return scene->name;
}

float scene_get_elapsed_time(struct scene * scene)
{
    return scene->elapsed_time;
}



void scene_set_id(struct scene * scene, int id)
{
    scene->id = id;
}

void scene_set_name(struct scene * scene, char * name)
{
    char * ptr = (char *)realloc(scene->name, strlen(name) + 1);
    assert(ptr != NULL);
    strcpy(ptr, name);
    scene->name = ptr;
}

void scene_set_elapsed_time(struct scene * scene, float elapsed_time)
{
    scene->elapsed_time = elapsed_time;
}



void scene_translate_elapsed_time(struct scene * scene, float delapsed_time)
{
    scene->elapsed_time += delapsed_time;
}



void scene_add_sprite(struct scene * scene, char * name, char * texture_filename, int x, int y, Color tint, bool is_visible)
{
    struct sprite sprite = sprite_create(texture_filename, x, y, tint, is_visible);
    array_append(&scene->sprites, &sprite);

    char * ptr = (char *)calloc(1, strlen(name) + 1);
    assert(ptr != NULL);
    strcpy(ptr, name);

    array_append(&scene->sprite_names, &ptr);
}

struct sprite * scene_get_sprite_from_index(struct scene * scene, size_t index)
{
    return (struct sprite *)array_get(&scene->sprites, index);
}

struct sprite * scene_get_sprite_from_name(struct scene * scene, char * name)
{
    for (int i = 0; i < array_get_count(&scene->sprite_names); ++i)
    {
        if (strcmp(name, *(char **)array_get(&scene->sprite_names, i)) == 0)
        {
            return (struct sprite *)array_get(&scene->sprites, i);
        }
    }

    return NULL;
}

size_t scene_get_sprites_count(struct scene * scene)
{
    return array_get_count(&scene->sprites);
}



void scene_add_button(struct scene * scene, char * name, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index, void(*on_pressed)(void), void(*on_down)(void), void(*on_released)(void))
{
    struct button button = button_create(x, y, width, height, color, is_enabled, mouse_cursor_index, on_pressed, on_down, on_released);
    array_append(&scene->buttons, &button);

    char * ptr = (char *)calloc(1, strlen(name) + 1);
    assert(ptr != NULL);
    strcpy(ptr, name);

    array_append(&scene->button_names, &ptr);
}

struct button * scene_get_button_from_index(struct scene * scene, size_t index)
{
    return (struct button *)array_get(&scene->buttons, index);
}

struct button * scene_get_button_from_name(struct scene * scene, char * name)
{
    for (int i = 0; i < array_get_count(&scene->button_names); ++i)
    {
        if (strcmp(name, *(char **)array_get(&scene->button_names, i)) == 0)
        {
            return (struct button *)array_get(&scene->buttons, i);
        }
    }

    return NULL;
}

size_t scene_get_buttons_count(struct scene * scene)
{
    return array_get_count(&scene->buttons);
}



void scene_add_sound(struct scene * scene, char * name, char * sound_filename)
{
    Sound sound = LoadSound(sound_filename);
    array_append(&scene->sounds, &sound);

    char * ptr = (char *)calloc(1, strlen(name) + 1);
    assert(ptr != NULL);
    strcpy(ptr, name);

    array_append(&scene->sound_names, &ptr);
}

Sound * scene_get_sound_from_index(struct scene * scene, size_t index)
{
    return (Sound *)array_get(&scene->sounds, index);
}

Sound * scene_get_sound_from_name(struct scene * scene, char * name)
{
    for (int i = 0; i < array_get_count(&scene->sound_names); ++i)
    {
        if (strcmp(name, *(char **)array_get(&scene->sound_names, i)) == 0)
        {
            return (Sound *)array_get(&scene->sounds, i);
        }
    }

    return NULL;
}

size_t scene_get_sounds_count(struct scene * scene)
{
    return array_get_count(&scene->sounds);
}



void scene_load(struct scene * scene)
{
    scene->load(scene);
}

void scene_unload(struct scene * scene)
{
    scene->unload(scene);

    for (int i = 0; i < array_get_count(&scene->sprites); ++i)
    {
        struct sprite * sprite = (struct sprite *)array_get(&scene->sprites, i);
        sprite_free(sprite);
    }

    array_clear(&scene->sprites);
    array_shrink(&scene->sprites);

    for (int i = 0; i < array_get_count(&scene->sprite_names); ++i)
    {
        char * ptr = *(char **)array_get(&scene->sprite_names, i);
        free(ptr);
    }

    array_clear(&scene->sprite_names);
    array_shrink(&scene->sprite_names);

    array_clear(&scene->buttons);
    array_shrink(&scene->buttons);

    for (int i = 0; i < array_get_count(&scene->button_names); ++i)
    {
        char * ptr = *(char **)array_get(&scene->button_names, i);
        free(ptr);
    }

    array_clear(&scene->button_names);
    array_shrink(&scene->button_names);

    for (int i = 0; i < array_get_count(&scene->sounds); ++i)
    {
        Sound * sound = (Sound *)array_get(&scene->sounds, i);
        UnloadSound(*sound);
    }

    array_clear(&scene->sounds);
    array_shrink(&scene->sounds);

    for (int i = 0; i < array_get_count(&scene->sound_names); ++i)
    {
        char * ptr = *(char **)array_get(&scene->sound_names, i);
        free(ptr);
    }

    array_clear(&scene->sound_names);
    array_shrink(&scene->sound_names);
}

void scene_enter(struct scene * scene)
{
    scene->enter(scene);
}

void scene_exit(struct scene * scene)
{
    scene->exit(scene);
}

void scene_update(struct scene * scene, float delta)
{
    scene->update(scene, delta);
}

void scene_draw(struct scene * scene)
{
    for (int i = 0; i < scene_get_sprites_count(scene); ++i)
    {
        struct sprite * sprite = scene_get_sprite_from_index(scene, i);
        sprite_draw(sprite);
    }

    for (int i = 0; i < scene_get_buttons_count(scene); ++i)
    {
        struct button * button = scene_get_button_from_index(scene, i);
        DrawRectangle(button_get_x(button), button_get_y(button), button_get_width(button), button_get_height(button), button_get_color(button));
    }

    scene->draw(scene);
}
