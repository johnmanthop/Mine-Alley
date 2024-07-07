#ifndef PLATFORM_MAP
#define PLATFORM_MAP

#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Drawable_Content.h"

class Platform_Map
{
public:
    sf::Texture tilemap;
    int width, height;
    std::vector<std::vector<TILE>> type_descriptor;
    std::vector<std::vector<Drawable_Static>> sprite_descriptor;
    double relative_position;
public:
    Platform_Map() {  }
    Platform_Map(const std::string &level_descriptor, const std::string &tilemap);

    void reset(const std::string &level_descriptor, const std::string &tilemap);

    int get_width()  const { return width; }
    int get_height() const { return height; }

    sf::Sprite& get_sprite(int w, int h) { return sprite_descriptor[h][w].get_sprite(); }
    TILE get_tile(int w, int h) const { return type_descriptor[h][w]; }

    std::vector<std::vector<TILE>> get_tile_map() const { return type_descriptor; }

    void roll_left();
    void roll_right();
};

#endif