#include "FSM.h"

bool FSM::timed() const 
{
    return table.at(current_state).count("end");
}

bool FSM::timed(const std::string &input) const
{
    // uses string as input
    return table.at(table.at(current_state).at(input)).count("end");
}

void FSM::construct_default_character_table()
{
    current_state = "idle_right";
    
    table["idle_right"]["NOP"]          = "idle_right";
    table["idle_right"]["D"]            = "walking_right";
    table["idle_right"]["A"]            = "walking_left";
    table["idle_right"]["attack"]       = "attacking_right";
    table["idle_right"]["collide"]      = "dash_right";
    table["idle_right"]["jump"]         = "jump_right";

    table["idle_left"]["NOP"]           = "idle_left";
    table["idle_left"]["D"]             = "walking_right";
    table["idle_left"]["A"]             = "walking_left";
    table["idle_left"]["attack"]        = "attacking_left";
    table["idle_left"]["collide"]       = "dash_left";
    table["idle_left"]["jump"]          = "jump_left";

    table["walking_right"]["NOP"]       = "idle_right";
    table["walking_right"]["D"]         = "walking_right";
    table["walking_right"]["A"]         = "walking_left";
    table["walking_right"]["attack"]    = "attacking_right";
    table["walking_right"]["collide"]   = "dash_right";
    table["walking_right"]["jump"]      = "jump_right";

    table["walking_left"]["NOP"]        = "idle_left";
    table["walking_left"]["D"]          = "walking_right";
    table["walking_left"]["A"]          = "walking_left";
    table["walking_left"]["attack"]     = "attacking_left";
    table["walking_left"]["collide"]    = "dash_left";
    table["walking_left"]["jump"]      = "jump_left";

    table["attacking_left"]["end"]      = "walking_left";
    table["attacking_left"]["NOP"]      = "attacking_left";
    table["attacking_left"]["D"]        = "attacking_left";
    table["attacking_left"]["A"]        = "attacking_left";
    table["attacking_left"]["attack"]   = "attacking_left";
    table["attacking_left"]["collide"]  = "attacking_left";
    table["attacking_left"]["jump"]     = "attacking_left";

    table["attacking_right"]["end"]     = "walking_right";
    table["attacking_right"]["NOP"]     = "attacking_right";
    table["attacking_right"]["D"]       = "attacking_right";
    table["attacking_right"]["A"]       = "attacking_right";
    table["attacking_right"]["attack"]  = "attacking_right";
    table["attacking_right"]["collide"] = "attacking_right";
    table["attacking_right"]["jump"]    = "attacking_right";

    table["dash_left"]["end"]           = "walking_left";
    table["dash_left"]["NOP"]           = "dash_left";
    table["dash_left"]["D"]             = "dash_left";
    table["dash_left"]["A"]             = "dash_left";
    table["dash_left"]["attack"]        = "dash_left";
    table["dash_left"]["collide"]       = "dash_left";
    table["dash_left"]["jump"]          = "dash_left";

    table["dash_right"]["end"]          = "walking_right";
    table["dash_right"]["NOP"]          = "dash_right";
    table["dash_right"]["D"]            = "dash_right";
    table["dash_right"]["A"]            = "dash_right";
    table["dash_right"]["attack"]       = "dash_right";
    table["dash_right"]["collide"]      = "dash_right";
    table["dash_right"]["jump"]         = "dash_right";

    table["jump_left"]["end"]           = "walking_left";
    table["jump_left"]["NOP"]           = "jump_left";
    table["jump_left"]["D"]             = "jump_left";
    table["jump_left"]["A"]             = "jump_left";
    table["jump_left"]["attack"]        = "jump_left";
    table["jump_left"]["collide"]       = "jump_left";
    table["jump_left"]["jump"]          = "jump_left";

    table["jump_right"]["end"]          = "walking_right";
    table["jump_right"]["NOP"]          = "jump_right";
    table["jump_right"]["D"]            = "jump_right";
    table["jump_right"]["A"]            = "jump_right";
    table["jump_right"]["attack"]       = "jump_right";
    table["jump_right"]["collide"]      = "jump_right";
    table["jump_right"]["jump"]         = "jump_right";
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