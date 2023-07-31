#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "raylib.h"
#include "array.h"

struct game_data_entry_bool
{
    char key[512];
    bool value;
};
struct game_data_entry_int
{
    char key[512];
    int value;
};
struct game_data_entry_float
{
    char key[512];
    float value;
};
struct game_data_entry_string
{
    char key[512];
    char value[512];
};
struct game_data_entry_color
{
    char key[512];
    Color value;
};

struct game_data
{
    struct array array_bool;
    struct array array_int;
    struct array array_float;
    struct array array_string;
    struct array array_color;
};

struct game_data game_data_create(void);
void game_data_init(struct game_data * game_data);
void game_data_free(struct game_data * game_data);
void game_data_reset(struct game_data * game_data);

void game_data_add_bool(struct game_data * game_data, char * key, bool value);
void game_data_add_int(struct game_data * game_data, char * key, int value);
void game_data_add_float(struct game_data * game_data, char * key, float value);
void game_data_add_string(struct game_data * game_data, char * key, char * value);
void game_data_add_color(struct game_data * game_data, char * key, Color value);

void game_data_remove_bool(struct game_data * game_data, char * key);
void game_data_remove_int(struct game_data * game_data, char * key);
void game_data_remove_float(struct game_data * game_data, char * key);
void game_data_remove_string(struct game_data * game_data, char * key);
void game_data_remove_color(struct game_data * game_data, char * key);

bool game_data_has_bool(struct game_data * game_data, char * key);
bool game_data_has_int(struct game_data * game_data, char * key);
bool game_data_has_float(struct game_data * game_data, char * key);
bool game_data_has_string(struct game_data * game_data, char * key);
bool game_data_has_color(struct game_data * game_data, char * key);

bool game_data_get_bool(struct game_data * game_data, char * key);
int game_data_get_int(struct game_data * game_data, char * key);
float game_data_get_float(struct game_data * game_data, char * key);
char * game_data_get_string(struct game_data * game_data, char * key);
Color game_data_get_color(struct game_data * game_data, char * key);

void game_data_set_bool(struct game_data * game_data, char * key, bool value);
void game_data_set_int(struct game_data * game_data, char * key, int value);
void game_data_set_float(struct game_data * game_data, char * key, float value);
void game_data_set_string(struct game_data * game_data, char * key, char * value);
void game_data_set_color(struct game_data * game_data, char * key, Color value);

#endif
