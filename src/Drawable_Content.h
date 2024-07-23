#ifndef DRAWABLE_CONTENT
#define DRAWABLE_CONTENT

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Drawable_Content 
{
public:
    virtual sf::Sprite& get_sprite() = 0;
    virtual sf::Sprite  copy_sprite() const = 0;
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
    Drawable_Static(const sf::Texture &tex, const sf::IntRect &rect, int x = 0, int y = 0);
    Drawable_Static(const Drawable_Static &s);

    Drawable_Static& operator=(const Drawable_Static &s);

    void reset(const sf::Texture &t, const sf::IntRect &rect, int x = 0, int y = 0);
    void reset(const std::string &file, int x = 0, int y = 0);

    sf::Vector2u get_texture_size()     const { return texture.getSize(); }
    sf::Vector2f get_sprite_position()  const { return sprite.getPosition(); }

    sf::Sprite&  get_sprite() override        { return sprite; }
    sf::Sprite   copy_sprite() const override { return sprite; }

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
    bool mirror;
public:
    Drawable_Animation() { mirror = false; }
    Drawable_Animation(const std::string &file, int no_of_frames_, int animation_speed_, int x = 0, int y = 0);
    Drawable_Animation(const Drawable_Animation &a);

    Drawable_Animation& operator=(const Drawable_Animation &a);

    void set_mirror(bool m) { mirror = m; }
    bool get_mirror() const { return mirror; }
    void reset(const std::string &file, int no_of_frames_, int animation_speed_, int x = 0, int y = 0);
    void reset_sprite();
    void tick();

    sf::Sprite& get_sprite() override;
    sf::Sprite  copy_sprite() const override { return current_sprite; }

    bool has_yielded() const;
};

#endif 