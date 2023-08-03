#ifndef SCENE_TEMPLATE_H
#define SCENE_TEMPLATE_H

#include "raylib.h"
#include "scene.h"
#include "scene_function_pointers.h"

static void scene_template_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
static void scene_template_free(void);

static void scene_template_load(void);
static void scene_template_unload(void);

static void scene_template_enter(void);
static void scene_template_exit(void);

static void scene_template_update(float delta);
static void scene_template_draw(void);

struct scene_function_pointers scene_template_get_function_pointers(void);

#endif
