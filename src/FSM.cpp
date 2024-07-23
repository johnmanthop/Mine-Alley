#include "FSM.h"

bool FSM::timed() const 
{
    return table.at(current_state).count("end");
}

void FSM::construct_default_character_table()
{
    current_state = "idle_right";
    
    table["idle_right"]["NOP"]      = "idle_right";
    table["idle_right"]["D"]        = "walking_right";
    table["idle_right"]["A"]        = "walking_left";
    table["idle_right"]["attack"]   = "attacking_right";

    table["idle_left"]["NOP"]       = "idle_left";
    table["idle_left"]["D"]         = "walking_right";
    table["idle_left"]["A"]         = "walking_left";
    table["idle_left"]["attack"]    = "attacking_left";

    table["walking_right"]["NOP"]   = "idle_right";
    table["walking_right"]["D"]     = "walking_right";
    table["walking_right"]["A"]     = "walking_left";
    table["walking_right"]["attack"]   = "attacking_right";

    table["walking_left"]["NOP"]    = "idle_left";
    table["walking_left"]["D"]      = "walking_right";
    table["walking_left"]["A"]      = "walking_left";
    table["walking_left"]["attack"] = "attacking_left";

    table["attacking_left"]["end"]  = "walking_left";
    table["attacking_left"]["NOP"]  = "attacking_left";
    table["attacking_left"]["D"]    = "attacking_left";
    table["attacking_left"]["A"]    = "attacking_left";
    table["attacking_left"]["attack"]   = "attacking_left";

    table["attacking_right"]["end"] = "walking_right";
    table["attacking_right"]["NOP"] = "attacking_right";
    table["attacking_right"]["D"]   = "attacking_right";
    table["attacking_right"]["A"]   = "attacking_right";
    table["attacking_right"]["attack"]   = "attacking_right";
}

void FSM::construct_default_enemy1_table()
{
    current_state = "idle_left";

    table["idle_left"]["NOP"]       = "idle_left";
    table["idle_left"]["left"]      = "walking_left";
    table["idle_left"]["right"]     = "walking_right";
    table["idle_left"]["hit"]       = "hit_left";
    table["idle_left"]["kill"]      = "dead_left";

    table["walking_left"]["NOP"]    = "idle_left";
    table["walking_left"]["left"]   = "walking_left";
    table["walking_left"]["right"]  = "walking_right";
    table["walking_left"]["hit"]    = "hit_left";
    table["walking_left"]["kill"]   = "dead_left";

    table["walking_right"]["NOP"]   = "idle_left";
    table["walking_right"]["left"]  = "walking_left";
    table["walking_right"]["right"] = "walking_right";
    table["walking_right"]["hit"]   = "hit_right";
    table["walking_right"]["kill"]  = "dead_right";

    table["hit_left"]["NOP"]        = "hit_left";
    table["hit_left"]["left"]       = "hit_left";
    table["hit_left"]["right"]      = "hit_left";
    table["hit_left"]["hit"]        = "hit_left";
    table["hit_left"]["end"]        = "walking_left";
    table["hit_left"]["kill"]       = "dead_left";

    table["hit_right"]["NOP"]        = "hit_right";
    table["hit_right"]["left"]       = "hit_right";
    table["hit_right"]["right"]      = "hit_right";
    table["hit_right"]["hit"]        = "hit_right";
    table["hit_right"]["end"]        = "walking_right";
    table["hit_right"]["kill"]       = "dead_right";

    table["dead_left"]["NOP"]        = "dead_left";
    table["dead_left"]["left"]       = "dead_left";
    table["dead_left"]["right"]      = "dead_left";
    table["dead_left"]["hit"]        = "dead_left";
    table["dead_left"]["end"]        = "dead_left";
    table["dead_left"]["kill"]       = "dead_left";

    table["dead_right"]["NOP"]       = "dead_right";
    table["dead_right"]["left"]      = "dead_right";
    table["dead_right"]["right"]     = "dead_right";
    table["dead_right"]["hit"]       = "dead_right";
    table["dead_right"]["end"]       = "dead_right";
    table["dead_right"]["kill"]      = "dead_right";
}