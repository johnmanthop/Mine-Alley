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
    table["idle_right"]["F"]   = "attacking_right";

    table["idle_left"]["NOP"] = "idle_left";
    table["idle_left"]["D"]   = "walking_right";
    table["idle_left"]["A"]   = "walking_left";
    table["idle_left"]["F"]   = "attacking_left";

    table["walking_right"]["NOP"] = "idle_right";
    table["walking_right"]["D"]   = "walking_right";
    table["walking_right"]["A"]   = "walking_left";
    table["walking_right"]["F"]   = "attacking_right";

    table["walking_left"]["NOP"] = "idle_left";
    table["walking_left"]["D"]   = "walking_right";
    table["walking_left"]["A"]   = "walking_left";
    table["walking_left"]["F"]   = "attacking_left";

    table["attacking_left"]["end"] = "idle_left";
    table["attacking_left"]["NOP"] = "attacking_left";
    table["attacking_left"]["D"]   = "walking_right";
    table["attacking_left"]["A"]   = "walking_left";
    table["attacking_left"]["F"]   = "attacking_left";

    table["attacking_right"]["end"] = "idle_right";
    table["attacking_right"]["NOP"] = "attacking_right";
    table["attacking_right"]["D"]   = "walking_right";
    table["attacking_right"]["A"]   = "walking_left";
    table["attacking_right"]["F"]   = "attacking_right";
}