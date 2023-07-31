#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "array.h"

struct scene
{
    float elapsed_time;
    Texture2D background_texture;
    struct array buttons;
};

struct scene scene_create(Texture2D background_texture);
void scene_init(struct scene * scene);
void scene_free(struct scene * scene);
void scene_reset(struct scene * scene, Texture2D background_texture);

float scene_get_elapsed_time(struct scene * scene);
Texture2D scene_get_background_texture(struct scene * scene);
struct array * scene_get_buttons(struct scene * scene);

void scene_set_elapsed_time(struct scene * scene, float elapsed_time);
void scene_set_background_texture(struct scene * scene, Texture2D background_texture);
void scene_set_buttons(struct scene * scene, struct array buttons);

void scene_translate_elapsed_time(struct scene * scene, float delapsed_time);

void scene_add_button(struct scene * scene, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index, void(*on_pressed)(void));
struct button * scene_get_button(struct scene * scene, size_t index);
size_t scene_get_buttons_count(struct scene * scene);

#endif
