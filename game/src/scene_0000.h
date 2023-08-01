#ifndef SCENE_0000_H
#define SCENE_0000_H

#include "raylib.h"
#include "scene.h"

void scene_0000_init(struct scene * scene_ptr, void(*set_scene_ptr)(int index));
void scene_0000_free(void);

void scene_0000_load(void);
void scene_0000_unload(void);

void scene_0000_enter(void);
void scene_0000_exit(void);

void scene_0000_update(float delta);
void scene_0000_draw(void);

static void on_released_button_new_game(void);
static void on_released_button_quit(void);

#endif
