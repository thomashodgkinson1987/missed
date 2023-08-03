#ifndef SCENE_0003_H
#define SCENE_0003_H

#include "raylib.h"
#include "scene.h"
#include "scene_function_pointers.h"

static void scene_0003_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
static void scene_0003_free(void);

static void scene_0003_load(void);
static void scene_0003_unload(void);

static void scene_0003_enter(void);
static void scene_0003_exit(void);

static void scene_0003_update(float delta);
static void scene_0003_draw(void);

struct scene_function_pointers scene_0003_get_function_pointers(void);

static void on_released_button_letter_floor(void);
static void on_released_button_letter_full_close(void);

#endif
