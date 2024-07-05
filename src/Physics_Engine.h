#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include "Constants.h"
#include "Character.h"
#include <vector>
#include <utility>

class Physics_Engine
{
public:
    enum MOVEMENT_TYPE{ LEFT, RIGHT, JUMP };
private:
    std::vector<std::vector<TILE>> tile_type_descriptor;
public:
    Physics_Engine() {}
    Physics_Engine(const Platform_Map &plt);

    void reset(const Platform_Map &plt);

    bool can_move_right(double x, double y) const;
    bool can_move_left (double x, double y) const;
    bool can_move_down (double x, double y) const;

    // player force, and terminate jump signal are returned
    std::pair<double, bool> calculate_force(const Character &ch) const;

    void tick_gravity(Character &ch);
};


#endif