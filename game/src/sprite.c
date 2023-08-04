#include "sprite.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>



struct sprite sprite_create(char * texture_filename, int x, int y, Color tint, bool is_visible)
{
    struct sprite sprite = (struct sprite){ 0 };

    sprite.texture = LoadTexture(texture_filename);
    sprite.x = x;
    sprite.y = y;
    sprite.tint = tint;
    sprite.is_visible = is_visible;

    return sprite;
}

void sprite_free(struct sprite * sprite)
{
    UnloadTexture(sprite->texture);

    sprite->texture = (Texture2D){ 0 };
    sprite->x = 0;
    sprite->y = 0;
    sprite->tint = BLANK;
    sprite->is_visible = false;
}

void sprite_reset(struct sprite * sprite, char * texture_filename, int x, int y, Color tint, bool is_visible)
{
    sprite_free(sprite);
    *sprite = sprite_create(texture_filename, x, y, tint, is_visible);
}



Texture2D sprite_get_texture(struct sprite * sprite)
{
    return sprite->texture;
}

int sprite_get_x(struct sprite * sprite)
{
    return sprite->x;
}

int sprite_get_y(struct sprite * sprite)
{
    return sprite->y;
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
