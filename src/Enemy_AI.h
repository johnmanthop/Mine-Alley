#ifndef ENEMY_AI
#define ENEMY_AI

#include <vector>
#include <string>

#include "Character.h"

class Enemy_AI
{
private:
    Character &player;
    std::vector<Character> &enemies;
    std::vector<std::string> next_actions;
private:
    int cycle_counter;
public:
    Enemy_AI(Character &pl, std::vector<Character> &enemies);

    int find_hit_enemy();
    std::vector<std::string> tick();
};

#endif