#include <iostream>
#include "Platform_Map.h"
#include "Physics_Engine.h"

Physics_Engine::Physics_Engine(const Platform_Map &plt)
{
    reset(plt);
}

void Physics_Engine::reset(const Platform_Map &plt)
{
    tile_type_descriptor = plt.get_tile_map();
}

bool Physics_Engine::can_move_left(double x, double y) const
{
    int normalized_x = ((x + (TILE_WIDTH / 2)) / TILE_WIDTH) + PLAYER_TILE_OFFSET - 1;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y_top    = (y / TILE_HEIGHT) + 1;
    int normalized_y_bottom = ((y + TILE_HEIGHT - 1) / TILE_HEIGHT) + 1;

    return ((tile_type_descriptor[normalized_y_top][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK) && 
           (tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK));
}

bool Physics_Engine::can_move_right(double x, double y) const
{
    int normalized_x = (x / TILE_WIDTH) + PLAYER_TILE_OFFSET;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y_top    = (y / TILE_HEIGHT) + 1;
    int normalized_y_bottom = ((y + TILE_HEIGHT - 1) / TILE_HEIGHT) + 1;

    return ((tile_type_descriptor[normalized_y_top][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK) && 
           (tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::VOID || tile_type_descriptor[normalized_y_bottom][normalized_x] == TILE::FINISH_BLOCK));}

bool Physics_Engine::can_move_down(double x, double y) const
{
    int normalized_x = ((x - 4) / TILE_WIDTH) + PLAYER_TILE_OFFSET;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y = (y / TILE_HEIGHT) + 2;

    return tile_type_descriptor[normalized_y][normalized_x] == TILE::VOID;
}

std::pair<double, bool> Physics_Engine::calculate_force(const Character &ch) const
{
    bool can_move_down_b = can_move_down(ch.get_absolute_x(), ch.get_absolute_y());

    // first two branches can be merged but there is a small bug
    if (ch.get_jumping_state() == 1)
    {
        return { -0.175 * (JUMP_LIMIT - ch.get_jump_counter()), false };
    }
    else if (ch.get_jumping_state() == 2 && can_move_down_b)
    {
        return { 1, false };
    }
    else
    {
        return { 0, true };
    }
}

void Physics_Engine::tick_gravity(Character &ch)
{
    if (!ch.is_jumping() && can_move_down(ch.get_absolute_x(), ch.get_absolute_y()))
    {
        ch.trigger_freefall();
    }
    else
    {
        ch.tick_jump();
    }
 
    auto p = calculate_force(ch);
    int force = (int)p.first;

    if (p.second) ch.reset_jump();

    ch.universal_move(0, force);
    
}