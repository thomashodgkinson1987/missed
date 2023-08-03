#ifndef SCENE_0002_H
#define SCENE_0002_H

#include "raylib.h"
#include "scene.h"
#include "scene_function_pointers.h"

static void scene_0002_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
static void scene_0002_free(void);

static void scene_0002_load(void);
static void scene_0002_unload(void);

static void scene_0002_enter(void);
static void scene_0002_exit(void);

static void scene_0002_update(float delta);
static void scene_0002_draw(void);

struct scene_function_pointers scene_0002_get_function_pointers(void);

static void on_released_button_exit(void);

#endif
