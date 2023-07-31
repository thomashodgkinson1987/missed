#include "raylib.h"
#include "sprite.h"



struct sprite sprite_create(int x, int y, Texture2D texture, Color tint, bool is_visible)
{
    return (struct sprite) { x, y, texture, tint, is_visible };
}

void sprite_free(struct sprite * sprite)
{
    sprite->x = 0;
    sprite->y = 0;
    UnloadTexture(sprite->texture);
    sprite->tint = BLANK;
    sprite->is_visible = false;
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
