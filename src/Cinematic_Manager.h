#ifndef CINEMATIC_MANAGER
#define CINEMATIC_MANAGER

#include "Keyboard_IO.h"
#include "Character.h"
#include "Generic_Map.h"
#include "Platform_Map.h"
#include "Collision_Engine.h"
#include "Constants.h"

class Cinematic_Manager
{
private:
    Character &player;
    Generic_Map &background_map;
    Platform_Map &platform_map;
    Collision_Engine collision_engine;
public:
    Cinematic_Manager(Character &pl, Generic_Map &bck, Platform_Map &plt);
    void reset();

    void handle_input();
    bool can_move_right() const;
    bool can_move_left () const;
    TILE get_tile_under_player() const;

    void move_player_or_map_right();
    void move_player_or_map_left();
};

#endif