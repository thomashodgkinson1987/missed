#ifndef SCENE_0000_H
#define SCENE_0000_H

#include "scene.h"

#include "raylib.h"

void scene_0000_load   (struct scene * scene);
void scene_0000_unload (struct scene * scene);

void scene_0000_enter  (struct scene * scene);
void scene_0000_exit   (struct scene * scene);

void scene_0000_update (struct scene * scene, float delta);
void scene_0000_draw   (struct scene * scene);

static void on_released_button_new_game (void);
static void on_released_button_quit     (void);

#endif
