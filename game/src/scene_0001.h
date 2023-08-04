#ifndef SCENE_0001_H
#define SCENE_0001_H

#include "button.h"
#include "scene.h"
#include "sprite.h"

void scene_0001_load(struct scene * scene);
void scene_0001_unload(struct scene * scene);

void scene_0001_enter(struct scene * scene);
void scene_0001_exit(struct scene * scene);

void scene_0001_update(struct scene * scene, float delta);
void scene_0001_draw(struct scene * scene);

static void on_released_button_quit(void);

#endif
