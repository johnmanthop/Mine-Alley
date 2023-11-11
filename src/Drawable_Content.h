#ifndef DRAWABLE_CONTENT
#define DRAWABLE_CONTENT

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Drawable_Content 
{
public:
    virtual sf::Sprite& get_sprite() = 0;
};

class Drawable_Static : public Drawable_Content
{
private:
    std::string texture_file;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Drawable_Static() {}
    Drawable_Static(const std::string &file, int x = 0, int y = 0);
    Drawable_Static(const Drawable_Static &s)
    {
        texture = s.texture;
        sprite.setTexture(texture);
        sprite.setPosition(s.get_sprite_x(), s.get_sprite_y());
    }

    void reset(const std::string &file, int x = 0, int y = 0);
    sf::Vector2u get_texture_size() const { return texture.getSize(); }
    sf::Vector2f get_sprite_position() const { return sprite.getPosition(); }
    sf::Sprite& get_sprite() override { return sprite; }
    float get_sprite_x() const { return sprite.getPosition().x; }
    float get_sprite_y() const { return sprite.getPosition().y; }
};

class Drawable_Animation : public Drawable_Content
{
private:
    sf::Sprite current_sprite;
    sf::Texture spritesheet;
    int no_of_frames;
    int animation_speed;
    int frame_height, frame_width;
    int spritesheet_height, spritesheet_width;
    int rect_left_top;
    int local_frame_tick_counter;
    int global_animation_tick_counter;
public:
    Drawable_Animation() {}
    Drawable_Animation(const std::string &file, int no_of_frames_, int animation_speed_, int x = 0, int y = 0);

    void reset(const std::string &file, int no_of_frames_, int animation_speed_, int x = 0, int y = 0);
    void reset_sprite();
    void tick();

    sf::Sprite& get_sprite() override { return current_sprite; }

    bool has_yielded() const 
    {
        return global_animation_tick_counter == (no_of_frames * animation_speed);
    }
};

#endif 