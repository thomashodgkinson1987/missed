#ifndef SCENE_TEMPLATE_H
#define SCENE_TEMPLATE_H

#include "scene.h"

void scene_template_load(struct scene * scene);
void scene_template_unload(struct scene * scene);

void scene_template_enter(struct scene * scene);
void scene_template_exit(struct scene * scene);

void scene_template_update(struct scene * scene, float delta);
void scene_template_draw(struct scene * scene);

#endif
