#include "FSM.h"

bool FSM::timed() const 
{
    return table.at(current_state).count("end");
}

void FSM::construct_default_character_table()
{
    current_state = "idle_right";
    
    table["idle_right"]["NOP"] = "idle_right";
    table["idle_right"]["D"]   = "walking_right";
    table["idle_right"]["A"]   = "walking_left";
    table["idle_right"]["attack"]   = "attacking_right";

    table["idle_left"]["NOP"] = "idle_left";
    table["idle_left"]["D"]   = "walking_right";
    table["idle_left"]["A"]   = "walking_left";
    table["idle_left"]["attack"]   = "attacking_left";

    table["walking_right"]["NOP"] = "idle_right";
    table["walking_right"]["D"]   = "walking_right";
    table["walking_right"]["A"]   = "walking_left";
    table["walking_right"]["attack"]   = "attacking_right";

    table["walking_left"]["NOP"] = "idle_left";
    table["walking_left"]["D"]   = "walking_right";
    table["walking_left"]["A"]   = "walking_left";
    table["walking_left"]["attack"]   = "attacking_left";

    table["attacking_left"]["end"] = "walking_left";
    table["attacking_left"]["NOP"] = "attacking_left";
    table["attacking_left"]["D"]   = "attacking_left";
    table["attacking_left"]["A"]   = "attacking_left";
    table["attacking_left"]["attack"]   = "attacking_left";

    table["attacking_right"]["end"] = "walking_right";
    table["attacking_right"]["NOP"] = "attacking_right";
    table["attacking_right"]["D"]   = "attacking_right";
    table["attacking_right"]["A"]   = "attacking_right";
    table["attacking_right"]["attack"]   = "attacking_right";
}