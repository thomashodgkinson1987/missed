#include <stdbool.h>
#include "raylib.h"
#include "button.h"



struct button button_create(int x, int y, int width, int height, Color color, bool is_enabled, int mouse_cursor_index, void(*on_pressed)(void))
{
    return (struct button) { x, y, width, height, color, is_enabled, mouse_cursor_index, on_pressed };
}



int button_get_x(struct button * button)
{
    return button->x;
}

int button_get_y(struct button * button)
{
    return button->y;
}

int button_get_width(struct button * button)
{
    return button->width;
}

int button_get_height(struct button * button)
{
    return button->height;
}

Color button_get_color(struct button * button)
{
    return button->color;
}

bool button_get_is_enabled(struct button * button)
{
    return button->is_enabled;
}

int button_get_mouse_cursor_index(struct button * button)
{
    return button->mouse_cursor_index;
}

void (*button_get_on_pressed(struct button * button))(void)
{
    return button->on_pressed;
}



void button_set_x(struct button * button, int x)
{
    button->x = x;
}

void button_set_y(struct button * button, int y)
{
    button->y = y;
}

void button_set_position(struct button * button, int x, int y)
{
    button->x = x;
    button->y = y;
}

void button_set_width(struct button * button, int width)
{
    button->width = width;
}

void button_set_height(struct button * button, int height)
{
    button->height = height;
}

void button_set_size(struct button * button, int width, int height)
{
    button->width = width;
    button->height = height;
}

void button_set_color(struct button * button, Color color)
{
    button->color = color;
}

void button_set_is_enabled(struct button * button, bool is_enabled)
{
    button->is_enabled = is_enabled;
}

void button_set_mouse_cursor_index(struct button * button, int mouse_cursor_index)
{
    button->mouse_cursor_index = mouse_cursor_index;
}

void button_set_on_pressed(struct button * button, void(*on_pressed)(void))
{
    button->on_pressed = on_pressed;
}



void button_toggle_is_enabled(struct button * button)
{
    button->is_enabled = !button->is_enabled;
}
