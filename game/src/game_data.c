#include "game_data.h"

#include <string.h>

struct game_data_entry_bool
{
    char key[512];
    bool value;
};
struct game_data_entry_int
{
    char key[512];
    int  value;
};
struct game_data_entry_float
{
    char  key[512];
    float value;
};
struct game_data_entry_string
{
    char key[512];
    char value[512];
};

struct game_data game_data_create (void)
{
    struct game_data game_data = (struct game_data){ 0 };

    game_data.array_bool = array_create(1, sizeof(struct game_data_entry_bool));
    array_init(&game_data.array_bool);

    game_data.array_int = array_create(1, sizeof(struct game_data_entry_int));
    array_init(&game_data.array_int);

    game_data.array_float = array_create(1, sizeof(struct game_data_entry_float));
    array_init(&game_data.array_float);

    game_data.array_string = array_create(1, sizeof(struct game_data_entry_string));
    array_init(&game_data.array_string);

    return game_data;
}
void game_data_free  (struct game_data * game_data)
{
    array_free(&game_data->array_bool);
    array_free(&game_data->array_int);
    array_free(&game_data->array_float);
    array_free(&game_data->array_string);

    game_data->array_bool   = (struct array){ 0 };
    game_data->array_int    = (struct array){ 0 };
    game_data->array_float  = (struct array){ 0 };
    game_data->array_string = (struct array){ 0 };
}
void game_data_reset (struct game_data * game_data)
{
    game_data_free(game_data);
    *game_data = game_data_create();
}

void game_data_add_bool   (struct game_data * game_data, char * key, bool   value)
{
    struct game_data_entry_bool entry = (struct game_data_entry_bool){ 0 };

    strcpy(entry.key, key);
    entry.value = value;

    array_append(&game_data->array_bool, &entry);
}
void game_data_add_int    (struct game_data * game_data, char * key, int    value)
{
    struct game_data_entry_int entry = (struct game_data_entry_int){ 0 };

    strcpy(entry.key, key);
    entry.value = value;

    array_append(&game_data->array_int, &entry);
}
void game_data_add_float  (struct game_data * game_data, char * key, float  value)
{
    struct game_data_entry_float entry = (struct game_data_entry_float){ 0 };

    strcpy(entry.key, key);
    entry.value = value;

    array_append(&game_data->array_float, &entry);
}
void game_data_add_string (struct game_data * game_data, char * key, char * value)
{
    struct game_data_entry_string entry = (struct game_data_entry_string){ 0 };

    strcpy(entry.key, key);
    strcpy(entry.value, value);

    array_append(&game_data->array_string, &entry);
}

void game_data_remove_bool   (struct game_data * game_data, char * key)
{
    int index = -1;

    for (int i = 0; i < array_get_count(&game_data->array_bool); ++i)
    {
        struct game_data_entry_bool * entry = (struct game_data_entry_bool *)array_get(&game_data->array_bool, i);
        if (strcmp(key, entry->key) == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        array_remove_at(&game_data->array_bool, index);
    }
}
void game_data_remove_int    (struct game_data * game_data, char * key)
{
    int index = -1;

    for (int i = 0; i < array_get_count(&game_data->array_int); ++i)
    {
        struct game_data_entry_int * entry = (struct game_data_entry_int *)array_get(&game_data->array_int, i);
        if (strcmp(key, entry->key) == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        array_remove_at(&game_data->array_int, index);
    }
}
void game_data_remove_float  (struct game_data * game_data, char * key)
{
    int index = -1;

    for (int i = 0; i < array_get_count(&game_data->array_float); ++i)
    {
        struct game_data_entry_float * entry = (struct game_data_entry_float *)array_get(&game_data->array_float, i);
        if (strcmp(key, entry->key) == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        array_remove_at(&game_data->array_float, index);
    }
}
void game_data_remove_string (struct game_data * game_data, char * key)
{
    int index = -1;

    for (int i = 0; i < array_get_count(&game_data->array_string); ++i)
    {
        struct game_data_entry_string * entry = (struct game_data_entry_string *)array_get(&game_data->array_string, i);
        if (strcmp(key, entry->key) == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        array_remove_at(&game_data->array_string, index);
    }
}

bool game_data_has_bool   (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_bool); ++i)
    {
        struct game_data_entry_bool * entry = (struct game_data_entry_bool *)array_get(&game_data->array_bool, i);
        if (strcmp(key, entry->key) == 0)
        {
            return true;
        }
    }

    return false;
}
bool game_data_has_int    (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_int); ++i)
    {
        struct game_data_entry_int * entry = (struct game_data_entry_int *)array_get(&game_data->array_int, i);
        if (strcmp(key, entry->key) == 0)
        {
            return true;
        }
    }

    return false;
}
bool game_data_has_float  (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_float); ++i)
    {
        struct game_data_entry_float * entry = (struct game_data_entry_float *)array_get(&game_data->array_float, i);
        if (strcmp(key, entry->key) == 0)
        {
            return true;
        }
    }

    return false;
}
bool game_data_has_string (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_string); ++i)
    {
        struct game_data_entry_string * entry = (struct game_data_entry_string *)array_get(&game_data->array_string, i);
        if (strcmp(key, entry->key) == 0)
        {
            return true;
        }
    }

    return false;
}

bool   game_data_get_bool   (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_bool); ++i)
    {
        struct game_data_entry_bool * entry = (struct game_data_entry_bool *)array_get(&game_data->array_bool, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    return false;
}
int    game_data_get_int    (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_int); ++i)
    {
        struct game_data_entry_int * entry = (struct game_data_entry_int *)array_get(&game_data->array_int, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    return -1;
}
float  game_data_get_float  (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_float); ++i)
    {
        struct game_data_entry_float * entry = (struct game_data_entry_float *)array_get(&game_data->array_float, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    return -1.0f;
}
char * game_data_get_string (struct game_data * game_data, char * key)
{
    for (int i = 0; i < array_get_count(&game_data->array_string); ++i)
    {
        struct game_data_entry_string * entry = (struct game_data_entry_string *)array_get(&game_data->array_string, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    return "";
}

bool   game_data_get_bool_default   (struct game_data * game_data, char * key, bool   default_value)
{
    for (int i = 0; i < array_get_count(&game_data->array_bool); ++i)
    {
        struct game_data_entry_bool * entry = (struct game_data_entry_bool *)array_get(&game_data->array_bool, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    game_data_add_bool(game_data, key, default_value);

    return default_value;
}
int    game_data_get_int_default    (struct game_data * game_data, char * key, int    default_value)
{
    for (int i = 0; i < array_get_count(&game_data->array_int); ++i)
    {
        struct game_data_entry_int * entry = (struct game_data_entry_int *)array_get(&game_data->array_int, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    game_data_add_int(game_data, key, default_value);

    return default_value;
}
float  game_data_get_float_default  (struct game_data * game_data, char * key, float  default_value)
{
    for (int i = 0; i < array_get_count(&game_data->array_float); ++i)
    {
        struct game_data_entry_float * entry = (struct game_data_entry_float *)array_get(&game_data->array_float, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    game_data_add_float (game_data, key, default_value);

    return default_value;
}
char * game_data_get_string_default (struct game_data * game_data, char * key, char * default_value)
{
    for (int i = 0; i < array_get_count(&game_data->array_string); ++i)
    {
        struct game_data_entry_string * entry = (struct game_data_entry_string *)array_get(&game_data->array_string, i);
        if (strcmp(key, entry->key) == 0)
        {
            return entry->value;
        }
    }

    game_data_add_string(game_data, key, default_value);

    return default_value;
}

void   game_data_set_bool   (struct game_data * game_data, char * key, bool   value)
{
    for (int i = 0; i < array_get_count(&game_data->array_bool); ++i)
    {
        struct game_data_entry_bool * entry = (struct game_data_entry_bool *)array_get(&game_data->array_bool, i);
        if (strcmp(key, entry->key) == 0)
        {
            entry->value = value;
            break;
        }
    }
}
void   game_data_set_int    (struct game_data * game_data, char * key, int    value)
{
    for (int i = 0; i < array_get_count(&game_data->array_int); ++i)
    {
        struct game_data_entry_int * entry = (struct game_data_entry_int *)array_get(&game_data->array_int, i);
        if (strcmp(key, entry->key) == 0)
        {
            entry->value = value;
            break;
        }
    }
}
void   game_data_set_float  (struct game_data * game_data, char * key, float  value)
{
    for (int i = 0; i < array_get_count(&game_data->array_float); ++i)
    {
        struct game_data_entry_float * entry = (struct game_data_entry_float *)array_get(&game_data->array_float, i);
        if (strcmp(key, entry->key) == 0)
        {
            entry->value = value;
            break;
        }
    }
}
void   game_data_set_string (struct game_data * game_data, char * key, char * value)
{
    for (int i = 0; i < array_get_count(&game_data->array_string); ++i)
    {
        struct game_data_entry_string * entry = (struct game_data_entry_string *)array_get(&game_data->array_string, i);
        if (strcmp(key, entry->key) == 0)
        {
            memset(entry->value, 0, 32);
            strcpy(entry->value, value);
            break;
        }
    }
}
