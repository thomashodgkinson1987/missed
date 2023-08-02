#ifndef SCENE_0001_H
#define SCENE_0001_H

#include "raylib.h"
#include "scene.h"

void scene_0001_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
void scene_0001_free(void);

void scene_0001_load(void);
void scene_0001_unload(void);

void scene_0001_enter(void);
void scene_0001_exit(void);

void scene_0001_update(float delta);
void scene_0001_draw(void);

static void on_released_button_quit(void);

#endif
