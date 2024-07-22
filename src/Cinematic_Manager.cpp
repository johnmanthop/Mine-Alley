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
    enemy_cycle = 0;
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

void Cinematic_Manager::check_dead_enemies()
{
    for (auto &en: enemies)
    {
        if (en.get_HP() < 0)
        {
            en.animation_manager.tick("kill");
        }
    }
}

void Cinematic_Manager::handle_enemies()
{
    std::vector<std::string> inputs(enemies.size());
    int hit_enemy_index = check_attacks();

    check_dead_enemies();

    for (auto &in: inputs) in = "NOP";

    if (enemy_cycle < ENEMY_CYCLE_LIMIT / 2)
    {
        for (int i = 0; i < enemies.size(); ++i)
        {
            if (hit_enemy_index != i && enemies[i].animation_manager.get_active_animation() != "hit_right")
            {
                inputs[i] = "right";
                move_enemy_right(i);
            }
            else
            {
                inputs[i] = "hit";
            }
        }

        enemy_cycle++;
    }
    else if (enemy_cycle < ENEMY_CYCLE_LIMIT)
    {
        for (int i = 0; i < enemies.size(); ++i)
        {
            if (hit_enemy_index != i && enemies[i].animation_manager.get_active_animation() != "hit_left")
            {
                inputs[i] = "left";
                move_enemy_left(i);
            }
            else
            {
                inputs[i] = "hit";
            }
        }

        enemy_cycle++;
    }
    else 
    {
        enemy_cycle = 0;
    }

    for (int i = 0; i < enemies.size(); ++i)
    {
        enemies[i].animation_manager.tick(inputs[i]);
    }
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

int Cinematic_Manager::check_attacks()
{
    int c = 0;

    std::string anim = player.animation_manager.get_active_animation();

    for (auto &en: enemies)
    {
        auto p = en.get_sprite().getPosition();
        if (player.get_sprite().getGlobalBounds().contains(p.x + 16, p.y) && Keyboard_IO::is_key_pressed_once(sf::Keyboard::Space))
        {
            bool enemy_left_of_player = player.get_sprite().getPosition().x > en.get_sprite().getPosition().x;
            bool player_facing_left = (anim == "idle_left" || anim == "walking_left" || anim == "attacking_left");
            
            if ((enemy_left_of_player && player_facing_left) || (!enemy_left_of_player && !player_facing_left))
            {
                en.add_HP(-10);
                return c;
            }
        }
        else 
        {
            c++;
        }
    }

    return -1;
}

void Cinematic_Manager::handle_input()
{
    std::string input = "NOP";

    if (Keyboard_IO::is_key_pressed_once(sf::Keyboard::Space))
    {
        Keyboard_IO::reset_key_press(sf::Keyboard::Space);
        input = "attack";
    }
    else if (
        Keyboard_IO::is_key_pressed(sf::Keyboard::D) &&
        player.animation_manager.get_active_animation() != "attacking_left" &&
        player.animation_manager.get_active_animation() != "attacking_right"
    )
    {
        if (can_move_right())
        {
            move_player_or_map_right();
            input = "D";
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
            move_player_or_map_left();
            input = "A";
        }
    }


    if (Keyboard_IO::is_key_pressed(sf::Keyboard::W) && !player.is_jumping())
    {
        player.trigger_jump();
    }

    player.animation_manager.tick(input);
}

void Cinematic_Manager::tick_gravity()
{
    for (auto &en: enemies)
    {
        physics_engine.tick_gravity(en);
    }

    physics_engine.tick_gravity(player);
}