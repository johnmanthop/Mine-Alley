#ifndef ENEMY_AI
#define ENEMY_AI

#include <vector>
#include <string>

#include "Character.h"

class Enemy_AI
{
private:
    Character                   &player;
    std::vector<Character>      &enemies;
    std::vector<int>            cycle_counters;
private:
    bool is_player_left_of_enemy (int index) const;
    bool is_player_right_of_enemy(int index) const;
public:
    Enemy_AI(Character &pl, std::vector<Character> &enemies);

    int find_hit_enemy();
    std::vector<std::pair<std::string, int>> tick();
};

#endif