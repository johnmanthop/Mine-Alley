#ifndef GENERIC_MAP_H_INCLUDED
#define GENERIC_MAP_H_INCLUDED


#include <string>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Drawable_Content.h"

class Generic_Map
{
private:
    std::vector<Drawable_Static> drawable_layers;
    double relative_position;
private:
    int get_right_border() const { return drawable_layers[drawable_layers.size() - 1].get_texture_size().x; }
public:
    Generic_Map() {}
    Generic_Map(const std::vector<std::string> &layer_files);
public:
    void reset(const std::vector<std::string> &layer_files);
    void roll_left();
    void roll_right();
    sf::Sprite& get_sprite(int layer_index) { return drawable_layers[layer_index].get_sprite(); }
    bool can_roll_left() const;
    bool can_roll_right() const;
    int get_layers() const { return drawable_layers.size(); }
};

#endif