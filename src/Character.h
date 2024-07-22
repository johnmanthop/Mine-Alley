#ifndef CHARACTER
#define CHARACTER

#include <iostream>
#include <map>
#include <string>

#include "Constants.h"
#include "Drawable_Content.h"
#include "Animation_Manager.h"

class Character
{
private:
    int HP;
    int height;
    int height_finetune;
    double y_position;
    int jump_counter;
    double universal_position;
    double relative_position;
    const double center_position;
    std::map<int, double> jumping_force_map;
public:
    Character(int y);
    void reset(int y);
    // no reason for this to be private
    Animation_Manager animation_manager;
    sf::Sprite& get_sprite();
    void inc_uposition() { universal_position += ROLL_STEP; }
    void dec_uposition() { universal_position -= ROLL_STEP; }
    void move_left(double speed = 1.f); 
    void move_right(double speed = 1.f);

    void set_height(int h)  { height = h; }
    int  get_height() const { return height; }

    void set_height_finetune(int h)  { height_finetune = h; }
    int  get_height_finetune() const { return height_finetune; }

    // move both static and animation sprites
    void universal_move(float x, float y);

    double get_relative_x() const { return relative_position; }
    double get_absolute_x() const { return universal_position; }
    double get_absolute_y() const { return y_position; }

    int get_HP() const { return HP; }
    void set_HP(int h) { HP = h; }
    void add_HP(int h) { HP += h; }

    bool can_move_left() const;
    bool can_move_right() const;
    bool is_at_center() const { return abs(relative_position - center_position) <= 2; }

    void trigger_jump() { jump_counter = 0; }
    void trigger_freefall() { jump_counter = JUMP_LIMIT; }
    int get_jump_counter() const { return jump_counter; }
    int get_jumping_state() const;
    void reset_jump()   { jump_counter = -1; }
    bool is_jumping() const { return jump_counter != -1; }
    void tick_jump();

    bool is_in_proximity(int p) const;
};

#endif