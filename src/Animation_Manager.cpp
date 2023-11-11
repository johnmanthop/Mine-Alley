#include <iostream>
#include "Animation_Manager.h"

void Animation_Manager::add_animation(const std::string &tag, const std::string &file, int no_of_frames_, int animation_speed_, int x, int y)
{
    animations[tag] = Drawable_Animation();
    animations[tag].reset(file, no_of_frames_, animation_speed_, x, y);
}

void Animation_Manager::set_active_animation(const std::string &tag)
{
   current_animation_tag = tag;
   is_animating_b = true;
}

void Animation_Manager::deactivate_animation()
{
   is_animating_b = false;
   animations[current_animation_tag].reset_sprite();
}

void Animation_Manager::tick_active_animation()
{
    animations[current_animation_tag].tick();
}

void Animation_Manager::move_all_sprites(float x, float y)
{
    for (auto &animation: animations)
    {
        animation.second.get_sprite().move({ x, y });
    }
}

sf::Sprite& Animation_Manager::get_sprite()
{
    return animations[current_animation_tag].get_sprite();
}

bool Animation_Manager::has_active_animation_yielded() const 
{
    // unfortunately [] has no const overload
    auto active_animation = animations.at(current_animation_tag);
    return active_animation.has_yielded();
}