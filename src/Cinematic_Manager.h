#ifndef CINEMATIC_MANAGER
#define CINEMATIC_MANAGER

#include "Keyboard_IO.h"
#include "Character.h"
#include "Generic_Map.h"
#include "Platform_Map.h"
#include "Physics_Engine.h"
#include "Constants.h"

class Cinematic_Manager
{
private:
    int enemy_cycle;
private:
    Character &player;
    std::vector<Character> &enemies;
    Generic_Map &background_map;
    Platform_Map &platform_map;
    Physics_Engine physics_engine;
private:
    void move_enemy_left(int index);
    void move_enemy_right(int index);
    void erase_dead_enemies();
public:
    Cinematic_Manager(Character &pl, std::vector<Character> &enemies, Generic_Map &bck, Platform_Map &plt);
    void reset();

    void tick_gravity();
    void handle_enemies(const std::vector<std::string> &action_list);
    void handle_input();
    
    bool can_move_right() const;
    bool can_move_left () const;
    TILE get_tile_under_player() const;

    void move_player_or_map_right();
    void move_player_or_map_left();
};

#endif