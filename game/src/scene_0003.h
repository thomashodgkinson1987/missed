#ifndef SCENE_0003_H
#define SCENE_0003_H

#include "raylib.h"
#include "scene.h"

void scene_0003_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
void scene_0003_free(void);

void scene_0003_load(void);
void scene_0003_unload(void);

void scene_0003_enter(void);
void scene_0003_exit(void);

void scene_0003_update(float delta);
void scene_0003_draw(void);

static void on_released_button_letter_floor(void);
static void on_released_button_letter_full_close(void);

#endif
