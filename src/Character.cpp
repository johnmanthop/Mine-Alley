#include <cmath>
#include "Character.h"
#include "FSM.h"

Character::Character():
    y_position(PLAYER_POS_Y),
    jump_counter(-1),
    universal_position(0),
    relative_position(100),
    center_position(100)
{
    reset();

    double f = 1.2;

    for (int i = 0; i < 12; ++i)
    {
        jumping_force_map[i] = (-1 + 0.2*i) * f;
    }
}

void Character::reset()
{
    y_position = PLAYER_POS_Y;
    jump_counter = -1;
    universal_position = 0;
    relative_position = 100;

    FSM fsm;
    fsm.construct_default_character_table();

    animation_manager.add_animation("idle_right", "assets/Character/Idle/Idle-Sheet.png", 4, 10, PLAYER_POS_X, PLAYER_POS_Y);
    animation_manager.add_animation("idle_left", "assets/Character/Idle/Idle-Sheet.png", 4, 10, PLAYER_POS_X, PLAYER_POS_Y);
    animation_manager.add_animation("walking_right", "assets/Character/Run/Run-Sheet.png", 8, 8, PLAYER_POS_X, PLAYER_POS_Y);
    animation_manager.add_animation("walking_left", "assets/Character/Run/Run-Sheet.png", 8, 8, PLAYER_POS_X, 95);
    animation_manager.add_animation("attacking_right", "assets/Character/Attack-01/Attack-01-Sheet.png", 8, 2, PLAYER_POS_X, PLAYER_POS_Y);
    animation_manager.add_animation("attacking_left", "assets/Character/Attack-01/Attack-01-Sheet.png", 8, 2, PLAYER_POS_X, PLAYER_POS_Y);
    
    animation_manager.animation_mirror("idle_left", true);
    animation_manager.animation_mirror("walking_left", true);
    animation_manager.animation_mirror("attacking_left", true);

    animation_manager.set_animation_fsm(fsm);
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

void Character::move_left()
{
    relative_position -= ROLL_STEP;
    universal_move(-ROLL_STEP, 0);
}

void Character::move_right()
{
    relative_position += ROLL_STEP;
    universal_move(ROLL_STEP, 0);
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