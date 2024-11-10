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
    sf::RectangleShape hp_bar;
    int HP;
    int hp_bar_max_size;
    int height;
    int height_finetune;
    double y_position;
    int jump_counter;
    double universal_position;
    double relative_position;
    double center_position;
public:
    Character(int x, int y);
    void reset(int x, int y);
    
    // no reason for this to be private
    Animation_Manager animation_manager;
    
    sf::Sprite& get_sprite();
    sf::RectangleShape& get_hp_bar_sprite() { return hp_bar; }
    
    void inc_uposition(double speed = 1.0f) { universal_position += ROLL_STEP * speed; }
    void dec_uposition(double speed = 1.0f) { universal_position -= ROLL_STEP * speed; }
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
    void add_HP(int h);

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