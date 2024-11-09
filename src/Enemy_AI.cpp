#include "Enemy_AI.h"
#include "Keyboard_IO.h"

Enemy_AI::Enemy_AI(Character &pl, std::vector<Character> &en):
    player(pl),
    enemies(en)
{ 
    cycle_counter = 0;
    next_actions = std::vector<std::string>(NO_ENEMIES);

    for (auto &action: next_actions) action = "NOP";
}

int Enemy_AI::find_hit_enemy()
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

std::vector<std::string> Enemy_AI::tick()
{
    int hit_enemy_index = find_hit_enemy();
    hit_enemy_index = -1;

    for (auto &ac: next_actions) ac = "NOP";

    if (cycle_counter < ENEMY_CYCLE_LIMIT / 2)
    {
        for (int i = 0; i < enemies.size(); ++i)
        {
            if (hit_enemy_index != i && enemies[i].animation_manager.get_active_animation() != "hit_right")
            {
                next_actions[i] = "right";
            }
            else
            {
                next_actions[i] = "hit";
            }
        }

        cycle_counter++;
    }
    else if (cycle_counter < ENEMY_CYCLE_LIMIT)
    {
        for (int i = 0; i < enemies.size(); ++i)
        {
            if (hit_enemy_index != i && enemies[i].animation_manager.get_active_animation() != "hit_left")
            {
                next_actions[i] = "left";
            }
            else
            {
                next_actions[i] = "hit";
            }
        }

        cycle_counter++;
    }
    else 
    {
        cycle_counter = 0;
    }

    return next_actions;
}