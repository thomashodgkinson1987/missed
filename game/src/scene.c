#include "raylib.h"
#include "scene.h"
#include "array.h"
#include "button.h"

struct scene scene_create(Texture2D background_texture)
{
    struct scene scene = (struct scene){ 0 };

    scene.elapsed_time = 0.0f;
    scene.background_texture = background_texture;
    scene.buttons = array_create(1, sizeof(struct button));

    return scene;
}

void scene_init(struct scene * scene)
{
    array_init(&scene->buttons);
}

void scene_free(struct scene * scene)
{
    scene->elapsed_time = 0.0f;
    UnloadTexture(scene->background_texture);
    array_free(&scene->buttons);
}

void scene_reset(struct scene * scene, Texture2D background_texture)
{
    scene_free(scene);
    *scene = scene_create(background_texture);
    scene_init(scene);
}



float scene_get_elapsed_time(struct scene * scene)
{
    return scene->elapsed_time;
}

Texture2D scene_get_background_texture(struct scene * scene)
{
    return scene->background_texture;
}

struct array * scene_get_buttons(struct scene * scene)
{
    return &scene->buttons;
}



void scene_set_elapsed_time(struct scene * scene, float elapsed_time)
{
    scene->elapsed_time = elapsed_time;
}

void scene_set_background_texture(struct scene * scene, Texture2D background_texture)
{
    scene->background_texture = background_texture;
}

void scene_set_buttons(struct scene * scene, struct array buttons)
{
    scene->buttons = buttons;
}



void scene_translate_elapsed_time(struct scene * scene, float delapsed_time)
{
    scene->elapsed_time += delapsed_time;
}



void scene_add_button(struct scene * scene, int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index, void(*on_pressed)(void))
{
    struct button button = button_create(x, y, width, height, color, is_enabled, mouse_cursor_index, on_pressed);
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
