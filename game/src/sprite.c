#include <string.h>
#include "raylib.h"
#include "sprite.h"



struct sprite sprite_create(int x, int y, char * texture_filename, Color tint, bool is_visible)
{
    struct sprite sprite = (struct sprite){ 0 };

    sprite.x = x;
    sprite.y = y;
    strcpy(sprite.texture_filename, texture_filename);
    sprite.texture = (Texture2D){ 0 };
    sprite.tint = tint;
    sprite.is_visible = is_visible;

    return sprite;
}

void sprite_init(struct sprite * sprite)
{
    sprite->texture = LoadTexture(sprite->texture_filename);
}

void sprite_free(struct sprite * sprite)
{
    sprite->x = 0;
    sprite->y = 0;
    memset(sprite->texture_filename, 0, 1024);
    UnloadTexture(sprite->texture);
    sprite->texture = (Texture2D){ 0 };
    sprite->tint = BLANK;
    sprite->is_visible = false;
}

void sprite_reset(struct sprite * sprite, int x, int y, char * texture_filename, Color tint, bool is_visible)
{
    sprite_free(sprite);
    *sprite = sprite_create(x, y, texture_filename, tint, is_visible);
    sprite_init(sprite);
}



int sprite_get_x(struct sprite * sprite)
{
    return sprite->x;
}

int sprite_get_y(struct sprite * sprite)
{
    return sprite->y;
}

int sprite_get_width(struct sprite * sprite)
{
    return sprite->texture.width;
}

int sprite_get_height(struct sprite * sprite)
{
    return sprite->texture.height;
}

char * sprite_get_texture_filename(struct sprite * sprite)
{
    return sprite->texture_filename;
}

Texture2D sprite_get_texture(struct sprite * sprite)
{
    return sprite->texture;
}

Color sprite_get_tint(struct sprite * sprite)
{
    return sprite->tint;
}

bool sprite_get_is_visible(struct sprite * sprite)
{
    return sprite->is_visible;
}



void sprite_set_x(struct sprite * sprite, int x)
{
    sprite->x = x;
}

void sprite_set_y(struct sprite * sprite, int y)
{
    sprite->y = y;
}

void sprite_set_position(struct sprite * sprite, int x, int y)
{
    sprite->x = x;
    sprite->y = y;
}

void sprite_set_texture_filename(struct sprite * sprite, char * texture_filename)
{
    memset(sprite->texture_filename, 0, 1024);
    strcpy(sprite->texture_filename, texture_filename);
}

void sprite_set_texture(struct sprite * sprite, Texture2D texture)
{
    sprite->texture = texture;
}

void sprite_set_tint(struct sprite * sprite, Color tint)
{
    sprite->tint = tint;
}

void sprite_set_is_visible(struct sprite * sprite, bool is_visible)
{
    sprite->is_visible = is_visible;
}



void sprite_toggle_is_visible(struct sprite * sprite)
{
    sprite->is_visible = !sprite->is_visible;
}



void sprite_draw(struct sprite * sprite)
{
    if (sprite->is_visible)
    {
        DrawTexture(sprite->texture, sprite->x, sprite->y, sprite->tint);
    }
}
