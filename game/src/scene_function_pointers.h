#ifndef SCENE_FUNCTION_POINTERS
#define SCENE_FUNCTION_POINTERS

#include "scene.h"
#include "scene_function_pointers.h"
#include "game_data.h"

struct scene_function_pointers
{
    void(*scene_init)(struct scene * scene, struct game_data * game_data, void(*set_scene)(int index));
    void(*scene_free)(void);
    void(*scene_load)(void);
    void(*scene_unload)(void);
    void(*scene_enter)(void);
    void(*scene_exit)(void);
    void(*scene_update)(float delta);
    void(*scene_draw)(void);
};

struct scene_function_pointers scene_function_pointers_create(
    void(*scene_init)(struct scene * scene, struct game_data * game_data, void(*set_scene)(int index)),
    void(*scene_free)(void),
    void(*scene_load)(void),
    void(*scene_unload)(void),
    void(*scene_enter)(void),
    void(*scene_exit)(void),
    void(*scene_update)(float delta),
    void(*scene_draw)(void)
);

#endif
