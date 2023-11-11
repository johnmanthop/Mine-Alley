#ifndef COLLISION_ENGINE
#define COLLISION_ENGINE

#include "Constants.h"
#include "Character.h"
#include <vector>

class Collision_Engine
{
public:
    enum MOVEMENT_TYPE{ LEFT, RIGHT, JUMP };
private:
    std::vector<std::vector<TILE>> tile_type_descriptor;
public:
    Collision_Engine() {}
    Collision_Engine(const Platform_Map &plt);

    void reset(const Platform_Map &plt);

    bool can_move_right(double x, double y) const;
    bool can_move_left (double x, double y) const;
    bool can_move_down (double x, double y) const;

    void tick_gravity(Character &ch);
};


#endif