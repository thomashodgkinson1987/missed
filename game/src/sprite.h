#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

struct sprite
{
    Texture2D texture;
    int x;
    int y;
    Color tint;
    bool is_visible;
};

struct sprite sprite_create(char * texture_filename, int x, int y, Color tint, bool is_visible);
void sprite_free(struct sprite * sprite);
void sprite_reset(struct sprite * sprite, char * texture_filename, int x, int y, Color tint, bool is_visible);

Texture2D sprite_get_texture(struct sprite * sprite);
int sprite_get_x(struct sprite * sprite);
int sprite_get_y(struct sprite * sprite);
Color sprite_get_tint(struct sprite * sprite);
bool sprite_get_is_visible(struct sprite * sprite);

void sprite_set_x(struct sprite * sprite, int x);
void sprite_set_y(struct sprite * sprite, int y);
void sprite_set_position(struct sprite * sprite, int x, int y);
void sprite_set_tint(struct sprite * sprite, Color tint);
void sprite_set_is_visible(struct sprite * sprite, bool is_visible);

void sprite_toggle_is_visible(struct sprite * sprite);

void sprite_draw(struct sprite * sprite);
void sprite_draw_with_offset(struct sprite * sprite, int offset_x, int offset_y);

#endif
