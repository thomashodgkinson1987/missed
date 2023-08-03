#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "array.h"

struct scene
{
    float elapsed_time;
    struct array sprites;
    struct array sprite_names;
    struct array buttons;
    struct array button_names;
    struct array sounds;
    struct array sound_names;
};

struct scene scene_create(void);
void scene_init(struct scene * scene);
void scene_free(struct scene * scene);
void scene_reset(struct scene * scene);

float scene_get_elapsed_time(struct scene * scene);

void scene_set_elapsed_time(struct scene * scene, float elapsed_time);

void scene_translate_elapsed_time(struct scene * scene, float delapsed_time);

void scene_add_sprite(struct scene * scene, char * name, int x, int y, char * texture_filename, Color tint, bool is_visible);
struct sprite * scene_get_sprite_from_index(struct scene * scene, size_t index);
struct sprite * scene_get_sprite_from_name(struct scene * scene, char * name);
size_t scene_get_sprites_count(struct scene * scene);

void scene_add_button(struct scene * scene, char * name, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index,
    void(*on_pressed)(void), void(*on_down)(void), void(*on_released)(void));
struct button * scene_get_button_from_index(struct scene * scene, size_t index);
struct button * scene_get_button_from_name(struct scene * scene, char * name);
size_t scene_get_buttons_count(struct scene * scene);

void scene_add_sound(struct scene * scene, char * name, char * sound_filename);
Sound * scene_get_sound_from_index(struct scene * scene, size_t index);
Sound * scene_get_sound_from_name(struct scene * scene, char * name);
size_t scene_get_sounds_count(struct scene * scene);

#endif
