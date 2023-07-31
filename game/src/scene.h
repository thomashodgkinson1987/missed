#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "array.h"

struct scene
{
    float elapsed_time;
    struct array sprites;
    struct array buttons;
};

struct scene scene_create(void);
void scene_init(struct scene * scene);
void scene_free(struct scene * scene);
void scene_reset(struct scene * scene);

float scene_get_elapsed_time(struct scene * scene);
struct array * scene_get_sprites(struct scene * scene);
struct array * scene_get_buttons(struct scene * scene);

void scene_set_elapsed_time(struct scene * scene, float elapsed_time);
void scene_set_sprites(struct scene * scene, struct array sprites);
void scene_set_buttons(struct scene * scene, struct array buttons);

void scene_translate_elapsed_time(struct scene * scene, float delapsed_time);

void scene_add_sprite(struct scene * scene, int x, int y, char * texture_filename, Color tint, bool is_visible);
struct sprite * scene_get_sprite(struct scene * scene, size_t index);
size_t scene_get_sprites_count(struct scene * scene);

void scene_add_button(struct scene * scene, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index, void(*on_pressed)(void));
struct button * scene_get_button(struct scene * scene, size_t index);
size_t scene_get_buttons_count(struct scene * scene);

#endif
