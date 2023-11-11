#include "Cinematic_Manager.h"

Cinematic_Manager::Cinematic_Manager(Character &pl, Generic_Map &bck, Platform_Map &plt):
    player(pl),
    background_map(bck),
    platform_map(plt)
{    
}

void Cinematic_Manager::reset()
{
    collision_engine.reset(platform_map);
}

bool Cinematic_Manager::can_move_right() const
{
    return (background_map.can_roll_left() || player.can_move_right()) && collision_engine.can_move_right(player.get_absolute_x(), player.get_absolute_y());
}

bool Cinematic_Manager::can_move_left() const 
{
    return (background_map.can_roll_right() || player.can_move_left()) && collision_engine.can_move_left(player.get_absolute_x(), player.get_absolute_y());
}

void Cinematic_Manager::move_player_or_map_right()
{
    player.inc_uposition();
    if (background_map.can_roll_left() && player.is_at_center())
    {
        background_map.roll_left();
        platform_map.roll_left();
    }
    else if (player.can_move_right()) 
    {
        player.move_right();
    }
}

void Cinematic_Manager::move_player_or_map_left()
{
    player.dec_uposition();
    if (background_map.can_roll_right() && player.is_at_center())
    {
        background_map.roll_right();
        platform_map.roll_right();
    }
    else if (player.can_move_left()) 
    {
        player.move_left();
    }
}

TILE Cinematic_Manager::get_tile_under_player() const 
{
    double x = player.get_absolute_x();
    double y = player.get_absolute_y();

    int normalized_x = ((x - 4) / TILE_WIDTH) + PLAYER_TILE_OFFSET;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y = (y / TILE_HEIGHT) + 2;

    return platform_map.get_tile(normalized_x, normalized_y);
}

void Cinematic_Manager::handle_input()
{
    if (player.animation_manager.is_animating()) player.animation_manager.tick_active_animation();
    if (Keyboard_IO::is_key_pressed(sf::Keyboard::D))
    {
        if (can_move_right())
        {
            move_player_or_map_right();

            if (!player.animation_manager.is_animating() ||
                player.animation_manager.get_active_animation() != "walking_right")
            {
                player.animation_manager.set_active_animation("walking_right");
            }
            else 
            {
                player.animation_manager.tick_active_animation();
            }
        }
        else 
        {
            player.animation_manager.deactivate_animation();
        }
    }
    else if (Keyboard_IO::is_key_pressed(sf::Keyboard::A))
    {
        if (can_move_left())
        {
            move_player_or_map_left();
            if (!player.animation_manager.is_animating() ||
                player.animation_manager.get_active_animation() != "walking_left")
            {
                player.animation_manager.set_active_animation("walking_left");
            }
            else 
            {
                player.animation_manager.tick_active_animation();
            }
        }
        else 
        {
            player.animation_manager.deactivate_animation();
        }
    }
    else 
    {
        player.animation_manager.deactivate_animation();
    }

    if (Keyboard_IO::is_key_pressed(sf::Keyboard::Space) && !player.get_jumping_state())
    {
        player.trigger_jump();
    }

    collision_engine.tick_gravity(player);
}