#ifndef SCENE_0002_H
#define SCENE_0002_H

#include "raylib.h"
#include "scene.h"

void scene_0002_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
void scene_0002_free(void);

void scene_0002_load(void);
void scene_0002_unload(void);

void scene_0002_enter(void);
void scene_0002_exit(void);

void scene_0002_update(float delta);
void scene_0002_draw(void);

static void on_released_button_exit(void);

#endif
