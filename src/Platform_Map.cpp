#include "Platform_Map.h"

Platform_Map::Platform_Map(const std::string &level_descriptor, const std::string &tilemap)
{
    reset(level_descriptor, tilemap);
}

void Platform_Map::reset(const std::string &level_descriptor, const std::string &tilemap_s)
{
    if (!tilemap.loadFromFile(tilemap_s))
    {
        std::cout << "Error loading tilemap\n";
        return;
    }

    std::ifstream file(level_descriptor);

    if (!file.is_open())
    {
        std::cout << "Cannot read level descriptor file\n";
        return;
    }

    file >> width;
    file >> height;
    
    char current_input;
    for (int h = 0; h < height; ++h)
    {
        type_descriptor.push_back(std::vector<TILE>());
        sprite_descriptor.push_back(std::vector<Drawable_Static>());

        for (int w = 0; w < width; ++w)
        {
            do
            {
                file.get(current_input);
            } while (current_input == 10);
            
            type_descriptor[h].emplace_back();
            sprite_descriptor[h].emplace_back();
            
            if (current_input == '0')
            {
                type_descriptor[h][w] = TILE::VOID;
                sprite_descriptor[h][w].reset( "assets/Misc/transp_block.png", w * 32, h * 32 );
            }
            else if (current_input == '1')
            {
                type_descriptor[h][w] = TILE::CONCRETE_BLOCK;
                sprite_descriptor[h][w].reset( tilemap, { { 64, 160 }, { 32, 32 } }, w * 32, h * 32);
            }
            else if (current_input == '2')
            {
                type_descriptor[h][w] = TILE::CONCRETE_BLOCK;
                sprite_descriptor[h][w].reset( tilemap, { { 13, 10 }, { 32, 32 } }, w * 32, h * 32 );
            }
            else if (current_input == '3')
            {
                type_descriptor[h][w] = TILE::CONCRETE_BLOCK;
                sprite_descriptor[h][w].reset( "assets/Misc/transp_block.png", w * 32, h * 32 );
            }
            else 
            {
                std::cout << "unknown char: " << (int)current_input << '\n';
            }
        }
    }
    
    file.close();
}

void Platform_Map::roll_left()
{
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            sprite_descriptor[h][w].get_sprite().move({ -ROLL_STEP, 0 });
        }
    }
}

void Platform_Map::roll_right()
{
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            sprite_descriptor[h][w].get_sprite().move({ ROLL_STEP, 0 });
        }
    }
}