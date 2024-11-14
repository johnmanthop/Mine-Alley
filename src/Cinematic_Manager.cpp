#include "Cinematic_Manager.h"

Cinematic_Manager::Cinematic_Manager(Character &pl, std::vector<Character> &en, Generic_Map &bck, Platform_Map &plt):
    player(pl),
    enemies(en),
    background_map(bck),
    platform_map(plt)
{    
}

void Cinematic_Manager::reset()
{
    physics_engine.reset(platform_map);
}

bool Cinematic_Manager::can_move_right() const
{
    return (background_map.can_roll_left() || player.can_move_right()) && physics_engine.can_move_right(player.get_absolute_x(), player.get_absolute_y());
}

bool Cinematic_Manager::can_move_left() const 
{
    return (background_map.can_roll_right() || player.can_move_left()) && physics_engine.can_move_left(player.get_absolute_x(), player.get_absolute_y());
}

void Cinematic_Manager::move_player_or_map_right()
{
    player.inc_uposition();

    if (background_map.can_roll_left() && player.is_at_center())
    {
        background_map.roll_left();
        platform_map.roll_left();
        for (auto &en: enemies)
        {
            en.move_left();
        }
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
        for (auto &en: enemies)
        {
            en.move_right();
        }
    }
    else if (player.can_move_left()) 
    {
        player.move_left();
    }
}

void Cinematic_Manager::move_enemy_left(int index)
{
    enemies[index].move_left(0.5);
}

void Cinematic_Manager::move_enemy_right(int index)
{
    enemies[index].move_right(0.5);
}

void Cinematic_Manager::erase_dead_enemies()
{
    int enemy_to_delete = -1;
    int c = 0;

    for (auto &en: enemies)
    {
        if (en.get_HP() <= 5)
        {
            en.animation_manager.tick("kill");
            enemy_to_delete = c;
        }
        c++;
    }

    if (enemy_to_delete != -1)
    {
        enemies.erase(enemies.begin() + enemy_to_delete);
    }  
}

void Cinematic_Manager::handle_enemy_interactions(const std::vector<std::pair<std::string, int>> &interaction_vector)
{
    erase_dead_enemies();
    enemy_interaction_vector = interaction_vector;
}

TILE Cinematic_Manager::get_tile_under_player() const 
{
    double x = player.get_absolute_x();
    double y = player.get_absolute_y();

    int normalized_x = ((x + PLAYER_X_OFFSET_MIDDLE) / TILE_SIZE) + PLAYER_TILE_OFFSET_MIDDLE;
    if (normalized_x < 0) normalized_x = 0;

    int normalized_y = (y / TILE_SIZE) + 2;

    return platform_map.get_tile(normalized_x, normalized_y);
}

void Cinematic_Manager::handle_input()
{
    last_player_input = "NOP";

    if (Keyboard_IO::is_key_pressed_once(sf::Keyboard::Space))
    {
        Keyboard_IO::reset_key_press(sf::Keyboard::Space);
        last_player_input = "attack";
    }
    else if (
        Keyboard_IO::is_key_pressed(sf::Keyboard::D) &&
        player.animation_manager.get_active_animation() != "attacking_left" &&
        player.animation_manager.get_active_animation() != "attacking_right"
    )
    {
        if (can_move_right())
        {
            last_player_input = "D";
        }

    }
    else if (
        Keyboard_IO::is_key_pressed(sf::Keyboard::A) &&
        player.animation_manager.get_active_animation() != "attacking_left" && 
        player.animation_manager.get_active_animation() != "attacking_right"
    
    )
    {
        if (can_move_left())
        {
            last_player_input = "A";
        }
    }


    if (Keyboard_IO::is_key_pressed(sf::Keyboard::W) && !player.is_jumping())
    {
        jump_triggered = true;
    }
    else 
    {
        jump_triggered = false;
    }
}

/*
 * TODO: make physics engine return an information structure 
 *       that cinematic manager will use to move the player instead of the physics engine moving the player directly
 */
void Cinematic_Manager::tick_gravity()
{
    for (auto &en: enemies)
    {
        physics_engine.tick_gravity(en);
    }

    physics_engine.tick_gravity(player);
}


void Cinematic_Manager::advance()
{
    bool dash_left = false;
    bool dash_right = false;

    tick_gravity();

    for (int i = 0; i < enemies.size(); ++i)
    {
        if (enemy_interaction_vector[i].first == "right")
        {
            enemies[i].move_right(0.5f);
        }
        else if (enemy_interaction_vector[i].first == "left")
        {
            enemies[i].move_left(0.5f);
        }

        if (enemy_interaction_vector[i].second == 1)
        {
            dash_left = true;
        }
        else if (enemy_interaction_vector[i].second == 2)
        {
            dash_right = true;
        }

        enemies[i].animation_manager.tick(enemy_interaction_vector[i].first);
    }

    // jump triggered comes from handle_input
    if (jump_triggered)
    {
        last_player_input = "jump";
        player.trigger_jump();
    }
    else if (dash_left)
    {
        last_player_input = "collide";
        player.move_left(10);
        player.dec_uposition(10);
    }
    else if (dash_right)
    {
        last_player_input = "collide";
        player.move_right(10);
        player.inc_uposition(10);
    }
    else if (last_player_input == "D")
    {
        move_player_or_map_right();
    }
    else if (last_player_input == "A")
    {
        move_player_or_map_left();
    }
    
    player.animation_manager.tick(last_player_input);
}