#ifndef SCENE_H
#define SCENE_H

#include "array.h"
#include "button.h"
#include "sprite.h"

#include "raylib.h"

struct scene
{
    int id;
    char * name;
    float elapsed_time;
    struct array sprites;
    struct array sprite_names;
    struct array buttons;
    struct array button_names;
    struct array sounds;
    struct array sound_names;
    void(*load)(struct scene * scene);
    void(*unload)(struct scene * scene);
    void(*enter)(struct scene * scene);
    void(*exit)(struct scene * scene);
    void(*update)(struct scene * scene, float delta);
    void(*draw)(struct scene * scene);
};

struct scene scene_create(
    int id,
    char * name,
    void(*load_ptr)(struct scene * scene),
    void(*unload_ptr)(struct scene * scene),
    void(*enter_ptr)(struct scene * scene),
    void(*exit_ptr)(struct scene * scene),
    void(*update_ptr)(struct scene * scene, float delta),
    void(*draw_ptr)(struct scene * scene));
void scene_free(struct scene * scene);
void scene_reset(
    struct scene * scene,
    int id,
    char * name,
    void(*load_ptr)(struct scene * scene),
    void(*unload_ptr)(struct scene * scene),
    void(*enter_ptr)(struct scene * scene),
    void(*exit_ptr)(struct scene * scene),
    void(*update_ptr)(struct scene * scene, float delta),
    void(*draw_ptr)(struct scene * scene));

int scene_get_id(struct scene * scene);
char * scene_get_name(struct scene * scene);
float scene_get_elapsed_time(struct scene * scene);

void scene_set_id(struct scene * scene, int id);
void scene_set_name(struct scene * scene, char * name);
void scene_set_elapsed_time(struct scene * scene, float elapsed_time);

void scene_translate_elapsed_time(struct scene * scene, float delapsed_time);

void scene_add_sprite(struct scene * scene, char * name, char * texture_filename, int x, int y, Color tint, bool is_visible);
struct sprite * scene_get_sprite_from_index(struct scene * scene, size_t index);
struct sprite * scene_get_sprite_from_name(struct scene * scene, char * name);
size_t scene_get_sprites_count(struct scene * scene);

void scene_add_button(struct scene * scene, char * name, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index, void(*on_pressed)(void), void(*on_down)(void), void(*on_released)(void));
struct button * scene_get_button_from_index(struct scene * scene, size_t index);
struct button * scene_get_button_from_name(struct scene * scene, char * name);
size_t scene_get_buttons_count(struct scene * scene);

void scene_add_sound(struct scene * scene, char * name, char * sound_filename);
Sound * scene_get_sound_from_index(struct scene * scene, size_t index);
Sound * scene_get_sound_from_name(struct scene * scene, char * name);
size_t scene_get_sounds_count(struct scene * scene);

void scene_load(struct scene * scene);
void scene_unload(struct scene * scene);
void scene_enter(struct scene * scene);
void scene_exit(struct scene * scene);
void scene_update(struct scene * scene, float delta);
void scene_draw(struct scene * scene);

#endif
