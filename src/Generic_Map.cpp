#include <iostream>

#include "Generic_Map.h"

Generic_Map::Generic_Map(const std::vector<std::string> &layer_files):
    relative_position(0)
{
    reset(layer_files);
}

void Generic_Map::reset(const std::vector<std::string> &layer_files)
{
    relative_position = 0;

    for (int i = 0; i < layer_files.size(); ++i)
    {
        drawable_layers.emplace_back(layer_files[i]);
    }
}

void Generic_Map::roll_left()
{
    relative_position -= ROLL_STEP;
    
    float factor = 1.f;
    for (int i = drawable_layers.size() - 1; i >= 1; --i)
    {
        drawable_layers[i].get_sprite().move({ -ROLL_STEP * factor, 0 });
        factor -= 0.2f;
    }
}

void Generic_Map::roll_right()
{
    relative_position += ROLL_STEP;
    
    float factor = 1.f;
    for (int i = drawable_layers.size() - 1; i >= 1; --i)
    {
        drawable_layers[i].get_sprite().move({ ROLL_STEP * factor, 0 });
        factor -= 0.2f;
    }
}

bool Generic_Map::can_roll_left() const
{
    return abs(relative_position) + MAIN_VIEW_WIDTH < get_right_border();
}

bool Generic_Map::can_roll_right() const
{
    return abs(relative_position) > 0;
}