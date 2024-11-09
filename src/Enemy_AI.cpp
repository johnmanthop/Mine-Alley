#include <algorithm>

#include "Enemy_AI.h"
#include "Keyboard_IO.h"

Enemy_AI::Enemy_AI(Character &pl, std::vector<Character> &en):
    player(pl),
    enemies(en)
{ 
    
    next_actions = std::vector<std::string> (NO_ENEMIES);
    counters     = std::vector<int>         (NO_ENEMIES);

    std::fill(next_actions.begin(), next_actions.end(), "NOP");
    std::fill(counters.begin(), counters.end(), 0);
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

bool Enemy_AI::is_player_left_of_enemy(int i) const
{
    auto p_x = player.get_sprite().getPosition().x;
    auto e_x = enemies[i].get_sprite().getPosition().x;

    return abs(p_x - e_x) < 45 && (p_x < e_x);
}

bool Enemy_AI::is_player_right_of_enemy(int i) const
{
    auto p_x = player.get_sprite().getPosition().x;
    auto e_x = enemies[i].get_sprite().getPosition().x;

    return abs(p_x - e_x) < 30 && (p_x > e_x);
}

std::vector<std::string> Enemy_AI::tick()
{
    int hit_enemy_index = find_hit_enemy();

    std::fill(next_actions.begin(), next_actions.end(), "NOP");

    /*
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
    */

    for (int i = 0; i < enemies.size(); ++i)
    {
        if (i == hit_enemy_index || enemies[i].animation_manager.get_active_animation().substr(0, 3) == "hit")
        {
            next_actions[i] = "hit";
            continue;
        }
        
        if (counters[i] < ENEMY_CYCLE_LIMIT / 2)
        {
            if (!is_player_left_of_enemy(i)) 
            {
                counters[i]++;
                next_actions[i] = "left";
            }
            else 
            {
                counters[i] = ENEMY_CYCLE_LIMIT / 2;
                next_actions[i] = "right";
            }
           
        }
        else if (counters[i] < ENEMY_CYCLE_LIMIT)
        {
            if (!is_player_right_of_enemy(i)) 
            {
                counters[i]++;
                next_actions[i] = "right";
            }
            else 
            {
                counters[i] = ENEMY_CYCLE_LIMIT;
                next_actions[i] = "left";
            }
        }
        else
        {
            counters[i] = 0;
        }
    }

    return next_actions;
}