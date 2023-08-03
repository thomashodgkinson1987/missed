#include "scene_function_pointers.h"
#include "scene.h"
#include "game_data.h"

struct scene_function_pointers scene_function_pointers_create(
    void(*scene_init)(struct scene * scene, struct game_data * game_data, void(*set_scene)(int index)),
    void(*scene_free)(void),
    void(*scene_load)(void),
    void(*scene_unload)(void),
    void(*scene_enter)(void),
    void(*scene_exit)(void),
    void(*scene_update)(float delta),
    void(*scene_draw)(void)
)
{
    struct scene_function_pointers scene_function_pointers = (struct scene_function_pointers){ 0 };

    scene_function_pointers.scene_init = scene_init;
    scene_function_pointers.scene_free = scene_free;
    scene_function_pointers.scene_load = scene_load;
    scene_function_pointers.scene_unload = scene_unload;
    scene_function_pointers.scene_enter = scene_enter;
    scene_function_pointers.scene_exit = scene_exit;
    scene_function_pointers.scene_update = scene_update;
    scene_function_pointers.scene_draw = scene_draw;

    return scene_function_pointers;
}
