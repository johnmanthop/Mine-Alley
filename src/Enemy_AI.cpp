#include <algorithm>

#include "Enemy_AI.h"
#include "Keyboard_IO.h"

Enemy_AI::Enemy_AI(Character &pl, std::vector<Character> &en):
    player(pl),
    enemies(en)
{ 
    cycle_counters = std::vector<int>         (NO_ENEMIES);
    std::fill(cycle_counters.begin(), cycle_counters.end(), 0);
}

int Enemy_AI::find_hit_enemy() const
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

/*
 * Return type is a vector of strings and ints
 * The string is the next action of the corresponding enemy
 * The int is a flag signifying weather a collision has happened between this enemy and the player and to which direction
 */
std::vector<std::pair<std::string, int>> Enemy_AI::tick()
{
    std::vector<std::pair<std::string, int>> return_v(NO_ENEMIES);
    std::fill(return_v.begin(), return_v.end(), std::make_pair<std::string, int>("NOP", 0));

    int hit_enemy_index = find_hit_enemy();


    for (int i = 0; i < enemies.size(); ++i)
    {
        if (i == hit_enemy_index || enemies[i].animation_manager.get_active_animation().substr(0, 3) == "hit")
        {
            return_v[i].first = "hit";
            continue;
        }
        
        if (cycle_counters[i] < ENEMY_CYCLE_LIMIT / 2)
        {
            if (!is_player_left_of_enemy(i)) 
            {
                cycle_counters[i]++;
                return_v[i].first = "left";
            }
            else 
            {
                cycle_counters[i] = ENEMY_CYCLE_LIMIT / 2;
                return_v[i].first = "right";
                return_v[i].second = 1;
            }
           
        }
        else if (cycle_counters[i] < ENEMY_CYCLE_LIMIT)
        {
            if (!is_player_right_of_enemy(i)) 
            {
                cycle_counters[i]++;
                return_v[i].first = "right";
            }
            else 
            {
                cycle_counters[i] = ENEMY_CYCLE_LIMIT;
                return_v[i].first = "left";
                return_v[i].second = 2;
            }
        }
        else
        {
            cycle_counters[i] = 0;
        }
    }

    return return_v;
}