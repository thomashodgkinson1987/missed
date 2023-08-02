#ifndef SCENE_TEMPLATE_H
#define SCENE_TEMPLATE_H

#include "raylib.h"
#include "scene.h"

void scene_template_init(struct scene * scene_ptr, struct game_data * game_data_ptr, void(*set_scene_ptr)(int index));
void scene_template_free(void);

void scene_template_load(void);
void scene_template_unload(void);

void scene_template_enter(void);
void scene_template_exit(void);

void scene_template_update(float delta);
void scene_template_draw(void);

#endif
