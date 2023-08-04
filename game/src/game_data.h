#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "array.h"

#include <stdbool.h>

struct game_data
{
    struct array array_bool;
    struct array array_int;
    struct array array_float;
    struct array array_string;
};

struct game_data game_data_create (void);
void game_data_free (struct game_data * game_data);
void game_data_reset (struct game_data * game_data);

void game_data_add_bool   (struct game_data * game_data, char * key, bool   value);
void game_data_add_int    (struct game_data * game_data, char * key, int    value);
void game_data_add_float  (struct game_data * game_data, char * key, float  value);
void game_data_add_string (struct game_data * game_data, char * key, char * value);

void game_data_remove_bool   (struct game_data * game_data, char * key);
void game_data_remove_int    (struct game_data * game_data, char * key);
void game_data_remove_float  (struct game_data * game_data, char * key);
void game_data_remove_string (struct game_data * game_data, char * key);

bool game_data_has_bool   (struct game_data * game_data, char * key);
bool game_data_has_int    (struct game_data * game_data, char * key);
bool game_data_has_float  (struct game_data * game_data, char * key);
bool game_data_has_string (struct game_data * game_data, char * key);

bool   game_data_get_bool   (struct game_data * game_data, char * key);
int    game_data_get_int    (struct game_data * game_data, char * key);
float  game_data_get_float  (struct game_data * game_data, char * key);
char * game_data_get_string (struct game_data * game_data, char * key);

bool   game_data_get_bool_default   (struct game_data * game_data, char * key, bool   default_value);
int    game_data_get_int_default    (struct game_data * game_data, char * key, int    default_value);
float  game_data_get_float_default  (struct game_data * game_data, char * key, float  default_value);
char * game_data_get_string_default (struct game_data * game_data, char * key, char * default_value);

void game_data_set_bool   (struct game_data * game_data, char * key, bool   value);
void game_data_set_int    (struct game_data * game_data, char * key, int    value);
void game_data_set_float  (struct game_data * game_data, char * key, float  value);
void game_data_set_string (struct game_data * game_data, char * key, char * value);

#endif
