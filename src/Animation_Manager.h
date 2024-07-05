#ifndef ANIMATION_MANAGER
#define ANIMATION_MANAGER

#include <string>
#include <map>

#include "FSM.h"
#include "Drawable_Content.h"

class Animation_Manager
{
private:
    FSM animation_fsm;
    std::map<std::string, Drawable_Animation> animations;
    std::string current_animation_tag;
public:
    Animation_Manager() {}
    void set_animation_fsm(const FSM &fsm) { animation_fsm = fsm; current_animation_tag = fsm.state(); }
    void add_animation(const std::string &tag, const std::string &file, int no_of_frames_, int animation_speed_, int x = 0, int y = 0);
    void animation_mirror(const std::string &tag, bool mirror) { animations[tag].set_mirror(mirror); }
    void tick(const std::string &input);
    sf::Sprite& get_sprite();
    void move_all_sprites(float x, float y);
    std::string get_active_animation() const { return current_animation_tag; }
    bool has_active_animation_yielded() const;
};

#endif