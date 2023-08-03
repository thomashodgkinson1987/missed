#ifndef SCENE_0000_H
#define SCENE_0000_H

#include "raylib.h"
#include "scene.h"
#include "scene_function_pointers.h"

static void scene_0000_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
static void scene_0000_free(void);

static void scene_0000_load(void);
static void scene_0000_unload(void);

static void scene_0000_enter(void);
static void scene_0000_exit(void);

static void scene_0000_update(float delta);
static void scene_0000_draw(void);

struct scene_function_pointers scene_0000_get_function_pointers(void);

static void on_released_button_new_game(void);
static void on_released_button_quit(void);

#endif
