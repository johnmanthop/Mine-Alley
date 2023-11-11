#include <iostream>
#include "Platform_Map.h"
#include "Collision_Engine.h"

Collision_Engine::Collision_Engine(const Platform_Map &plt)
{
    reset(plt);
}

void Collision_Engine::reset(const Platform_Map &plt)
{
    tile_type_descriptor = plt.get_tile_map();
}

bool Collision_Engine::can_move_left(double x, double y) const
{
    int normalized_x = ((x + (TILE_WIDTH / 2)) / TILE_WIDTH) + PLAYER_TILE_OFFSET - 1;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y_top    = (y / TILE_HEIGHT) + 1;
    int normalized_y_bottom = ((y + TILE_HEIGHT - 1) / TILE_HEIGHT) + 1;

    return ((tile_type_descriptor[normalized_y_top][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK) && 
           (tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK));
}

bool Collision_Engine::can_move_right(double x, double y) const
{
    int normalized_x = (x / TILE_WIDTH) + PLAYER_TILE_OFFSET;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y_top    = (y / TILE_HEIGHT) + 1;
    int normalized_y_bottom = ((y + TILE_HEIGHT - 1) / TILE_HEIGHT) + 1;

    return ((tile_type_descriptor[normalized_y_top][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK) && 
           (tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK));}

bool Collision_Engine::can_move_down(double x, double y) const
{
    int normalized_x = ((x - 4) / TILE_WIDTH) + PLAYER_TILE_OFFSET;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y = (y / TILE_HEIGHT) + 2;

    return tile_type_descriptor[normalized_y][normalized_x] == TILE::VOID;
}

void Collision_Engine::tick_gravity(Character &ch)
{
    double force;

    ch.tick_jump();
    if (ch.get_jumping_state())
    {
        force = ch.get_jumping_force();
    }
    else 
    {
        force = ch.get_max_gravity_force();
    }

    // negative force means upward movement
    if (force < 0)
    {
        ch.universal_move(0, force);
    }
    else if (can_move_down(ch.get_absolute_x(), ch.get_absolute_y()))
    {
        ch.universal_move(0, force);
    }
}