#ifndef ANIMATION_MANAGER
#define ANIMATION_MANAGER

#include <string>
#include <map>

#include "Drawable_Content.h"

class Animation_Manager
{
private:
    std::map<std::string, Drawable_Animation> animations;
    std::string current_animation_tag;
    bool is_animating_b;
public:
    Animation_Manager()
    {
        is_animating_b = false;
    }

    void add_animation(const std::string &tag, const std::string &file, int no_of_frames_, int animation_speed_, int x = 0, int y = 0);
    void set_active_animation(const std::string &tag);
    void deactivate_animation();
    void tick_active_animation();
    bool is_animating() const { return is_animating_b; }
    sf::Sprite& get_sprite();
    void move_all_sprites(float x, float y);
    std::string get_active_animation() const { return current_animation_tag; }
    bool has_active_animation_yielded() const;
};

#endif