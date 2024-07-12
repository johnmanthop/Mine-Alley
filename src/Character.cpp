#include <cmath>
#include "Character.h"
#include "FSM.h"

Character::Character(int y):
    center_position(MAIN_VIEW_WIDTH / 2 + 60)
{
    reset(y);
}

void Character::reset(int y)
{
    y_position = y;
    jump_counter = -1;
    universal_position = 0;
    relative_position  = 200;

    animation_manager.clear();
}

sf::Sprite& Character::get_sprite()
{
    return animation_manager.get_sprite();
}

void Character::universal_move(float x, float y)
{
    y_position += y;
    animation_manager.move_all_sprites(x, y);
}

void Character::move_left(double speed)
{
    relative_position -= speed * ROLL_STEP;
    universal_move(-speed * ROLL_STEP, 0);
}

void Character::move_right(double speed)
{
    relative_position += speed * ROLL_STEP;
    universal_move(speed * ROLL_STEP, 0);
}

bool Character::is_in_proximity(int p) const
{
    return abs(universal_position - p) < 10;
}

bool Character::can_move_left() const 
{
    return relative_position > 0;
}

bool Character::can_move_right() const 
{
    return relative_position < MAIN_VIEW_WIDTH - 12;
}

void Character::tick_jump()
{
    if (jump_counter != -1)
    {
        jump_counter++;
    }
}

int Character::get_jumping_state() const 
{
    // not jumping, upward movement, downward movement
    if (jump_counter == -1) return 0;       
    else if (jump_counter < JUMP_LIMIT) return 1;
    else return 2;
}