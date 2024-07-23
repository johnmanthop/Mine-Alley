#include <iostream>

#include "Drawable_Content.h"

Drawable_Static::Drawable_Static(const std::string &file, int x, int y)
{
    reset(file, x, y);
}

Drawable_Static::Drawable_Static(const sf::Texture &tex, const sf::IntRect &rect, int x, int y)
{
    reset(tex, rect, x, y);
}

Drawable_Static::Drawable_Static(const Drawable_Static &s)
{
    texture_file = s.texture_file;
    texture = s.texture;
    sprite = s.copy_sprite();

    sprite.setTexture(texture);
}

Drawable_Static& Drawable_Static::operator=(const Drawable_Static &s)
{
    texture_file = s.texture_file;
    texture = s.texture;
    sprite = s.copy_sprite();

    sprite.setTexture(texture);

    return *this;
}

void Drawable_Static::reset(const std::string &file, int x, int y)
{
    if (!texture.loadFromFile(file))
    {
        std::cout << "Error loading texture\n";
    }
    
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Drawable_Static::reset(const sf::Texture &tex, const sf::IntRect &rect, int x, int y)
{
    // TODO: this needs to be revisited
    texture = tex;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(x, y);
}

Drawable_Animation::Drawable_Animation(const std::string &file, int no_of_frames_, int animation_speed_, int x, int y)
{
    reset(file, no_of_frames_, animation_speed_, x, y);
}

Drawable_Animation::Drawable_Animation(const Drawable_Animation &a)
{
    spritesheet                         = a.spritesheet;
    current_sprite                      = a.copy_sprite();
    current_sprite.setTexture(spritesheet);

    no_of_frames                        = a.no_of_frames;
    animation_speed                     = a.animation_speed;
    frame_height                        = a.frame_height;
    frame_width                         = a.frame_width;
    spritesheet_height                  = a.spritesheet_height;
    spritesheet_width                   = a.spritesheet_width;
    rect_left_top                       = a.rect_left_top;
    local_frame_tick_counter            = a.local_frame_tick_counter;
    global_animation_tick_counter       = a.global_animation_tick_counter;
    mirror                              = a.mirror;
}

Drawable_Animation& Drawable_Animation::operator=(const Drawable_Animation &a)
{
    spritesheet                         = a.spritesheet;
    current_sprite                      = a.copy_sprite();
    current_sprite.setTexture(spritesheet);

    no_of_frames                        = a.no_of_frames;
    animation_speed                     = a.animation_speed;
    frame_height                        = a.frame_height;
    frame_width                         = a.frame_width;
    spritesheet_height                  = a.spritesheet_height;
    spritesheet_width                   = a.spritesheet_width;
    rect_left_top                       = a.rect_left_top;
    local_frame_tick_counter            = a.local_frame_tick_counter;
    global_animation_tick_counter       = a.global_animation_tick_counter;
    mirror                              = a.mirror;

    return *this;
}

sf::Sprite& Drawable_Animation::get_sprite() 
{
    if (mirror)
    {
        current_sprite.setOrigin(current_sprite.getTextureRect().width, 0);
        current_sprite.setScale(-1.f, 1.f);
        
        return current_sprite;
    }
    else
    {
        return current_sprite;
    }
}

void Drawable_Animation::reset(const std::string &file, int no_of_frames_, int animation_speed_, int x, int y)
{
    if (!spritesheet.loadFromFile(file))
    {
        std::cout << "Error loading spritesheet\n";
    }

    local_frame_tick_counter = 1;
    global_animation_tick_counter = 1;
    no_of_frames        = no_of_frames_;
    animation_speed     = animation_speed_;
    rect_left_top       = 0;

    spritesheet_width  = spritesheet.getSize().x;
    spritesheet_height = spritesheet.getSize().y;

    frame_height = spritesheet_height;
    frame_width = spritesheet_width / no_of_frames;

    current_sprite.setTexture(spritesheet);
    current_sprite.setTextureRect({ { 0, 0 }, { frame_width, frame_height } });
    current_sprite.setPosition(x, y);
}

void Drawable_Animation::reset_sprite()
{
    current_sprite.setTextureRect({ { 0, 0 }, { frame_width, frame_height } });
}

void Drawable_Animation::tick()
{
    global_animation_tick_counter++;

    int former_left = current_sprite.getTextureRect().left;

    if (local_frame_tick_counter == animation_speed)
    {
        // that means the frame needs to wraparound
        if (former_left + frame_width >= spritesheet_width)
        {
            current_sprite.setTextureRect({ { 0, 0 }, { frame_width, frame_height } });
            global_animation_tick_counter = 1;
        }
        else 
        {
            current_sprite.setTextureRect({ { former_left + frame_width, 0 }, { frame_width, frame_height } });
        }
        local_frame_tick_counter = 1;
    }
    else
    {
        local_frame_tick_counter++;
    }
}

bool Drawable_Animation::has_yielded() const
{
    return global_animation_tick_counter >= (no_of_frames * animation_speed);
}