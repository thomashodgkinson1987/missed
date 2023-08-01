#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include "raylib.h"

struct button
{
    int x;
    int y;
    int width;
    int height;
    Color color;
    bool is_enabled;
    int mouse_cursor_index;
    bool was_mouse_over;
    bool is_mouse_over;
    bool was_down;
    bool is_down;
    void(*on_pressed)(void);
    void(*on_down)(void);
    void(*on_released)(void);
};

struct button button_create(int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index,
    void(*on_pressed)(void), void(*on_down)(void), void(*on_released)(void));

int button_get_x(struct button * button);
int button_get_y(struct button * button);
int button_get_width(struct button * button);
int button_get_height(struct button * button);
Color button_get_color(struct button * button);
bool button_get_is_enabled(struct button * button);
int button_get_mouse_cursor_index(struct button * button);
bool button_get_was_mouse_over(struct button * button);
bool button_get_is_mouse_over(struct button * button);
bool button_get_was_down(struct button * button);
bool button_get_is_down(struct button * button);
void (*button_get_on_pressed(struct button * button))(void);
void (*button_get_on_down(struct button * button))(void);
void (*button_get_on_released(struct button * button))(void);

void button_set_x(struct button * button, int x);
void button_set_y(struct button * button, int y);
void button_set_position(struct button * button, int x, int y);
void button_set_width(struct button * button, int width);
void button_set_height(struct button * button, int height);
void button_set_size(struct button * button, int width, int height);
void button_set_color(struct button * button, Color color);
void button_set_is_enabled(struct button * button, bool is_enabled);
void button_set_mouse_cursor_index(struct button * button, int mouse_cursor_index);
void button_set_was_mouse_over(struct button * button, bool was_mouse_over);
void button_set_is_mouse_over(struct button * button, bool is_mouse_over);
void button_set_was_down(struct button * button, bool was_down);
void button_set_is_down(struct button * button, bool is_down);
void button_set_on_pressed(struct button * button, void(*on_pressed)(void));
void button_set_on_down(struct button * button, void(*on_down)(void));
void button_set_on_released(struct button * button, void(*on_released)(void));

void button_toggle_is_enabled(struct button * button);

#endif
