#ifndef SCENE_0001_H
#define SCENE_0001_H

#include "raylib.h"
#include "scene.h"
#include "scene_function_pointers.h"

static void scene_0001_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
static void scene_0001_free(void);

static void scene_0001_load(void);
static void scene_0001_unload(void);

static void scene_0001_enter(void);
static void scene_0001_exit(void);

static void scene_0001_update(float delta);
static void scene_0001_draw(void);

struct scene_function_pointers scene_0001_get_function_pointers(void);

static void on_released_button_quit(void);

#endif
