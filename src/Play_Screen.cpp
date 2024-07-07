#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Play_Screen.h"
#include "Constants.h"

Play_Screen::Play_Screen(const Screen_Configuration &config):
    interaction_board("assets/other/board.png"),
    cinematic_manager(player, background_map, platform_map)
{
    configuration = config;
    reset(configuration);
}

void Play_Screen::reset(const Screen_Configuration &config)
{
    player.reset();
    cinematic_manager.reset();

    main_view.reset({ 0, 0, MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT });

    interaction_board.get_sprite().setScale(0.3, 0.3);
    interaction_board.get_sprite().setPosition({ 45, 150 });

    background_map.reset(config.layer_files);
    platform_map.reset(config.level_descriptor_file, "assets/Misc/Tiles.png");

    name_tag        = config.name_tag;
    next_screen_s   = name_tag;
    triggers        = config.triggers;

    cinematic_manager.reset();
}

void Play_Screen::handle_drawing(Renderer &renderer)
{
    renderer.clear();

    renderer.set_view(main_view);

    for (int i = 0; i < background_map.get_layer_no(); ++i)
    {
        renderer.draw(background_map.get_sprite(i));
    }

    for (int h = 0; h < platform_map.get_height(); ++h)
    {
        for (int w = 0; w < platform_map.get_width(); ++w)
        {
            renderer.draw(platform_map.get_sprite(w, h));
        }
    }
    
    renderer.draw(player.get_sprite());
    
    renderer.display();
}


void Play_Screen::handle_input()
{
    cinematic_manager.handle_input();
}

void Play_Screen::handle_action(const std::string &action)
{
    if (action == "to_scene1")
    {
        next_screen_s = "scene1";
    }
    else if (action == "to_scene2")
    {
        next_screen_s = "scene2";
    }
    else if (action == "to_scene3")
    {
        next_screen_s = "scene3";
    }
    else if (action == "to_scene3a")
    {
        next_screen_s = "scene3a";
    }
    else if (action == "to_exp1")
    {
        next_screen_s = "exp1";
    }
}

std::string Play_Screen::next_screen()
{
    auto to_return = next_screen_s;
    next_screen_s = name_tag;

    return to_return;
}

void Play_Screen::handle_triggers()
{
    trigger_on = false;
    for (auto &trigger: triggers)
    {
        if (player.is_in_proximity(trigger.position))
        {
            active_trigger = trigger;
            trigger_on = true;
            if (Keyboard_IO::is_key_pressed_once(sf::Keyboard::E))
            {
                handle_action(trigger.action);
            }
        }
    }
}

void Play_Screen::handle_frame(Renderer &renderer)
{
    if (!player_dying && !player_dead && !player_won)
    {
        handle_input();
        handle_triggers();
    }
    

    std::vector<sf::Event> event_list = renderer.get_event_list();

    for (sf::Event &event : event_list)
    {
        if (event.type == sf::Event::Closed)
        {
            renderer.close();
        }
    }

    handle_drawing(renderer);
}
