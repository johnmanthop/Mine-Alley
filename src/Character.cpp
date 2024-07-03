#include <cmath>
#include "Character.h"

Character::Character():
    character_static("assets/characters/player_static.png"),
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

    character_static.get_sprite().setPosition({ PLAYER_POS_X, PLAYER_POS_Y });
    
    animation_manager.add_animation("walking_right", "assets/characters/player_walking_right.png", 4, 17, 100, 128);
    animation_manager.add_animation("walking_left", "assets/characters/player_walking_left.png", 4, 17, 100, 128);
    animation_manager.set_active_animation("walking_right");
}

sf::Sprite& Character::get_sprite()
{
    if (animation_manager.is_animating())
    {
        return animation_manager.get_sprite();
    }
    else 
    {
        return character_static.get_sprite();
    }
}

void Character::universal_move(float x, float y)
{
    y_position += y;
    animation_manager.move_all_sprites(x, y);
    character_static.get_sprite().move({ x, y });
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
    if (jump_counter == -1) return 0;       // not jumping
    else if (jump_counter < JUMP_LIMIT) return 1;   // upward movement
    else return 2;                          // downward movement
}