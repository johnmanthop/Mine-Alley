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
    player_dying    = false;
    player_dead     = false;
    trigger_on      = false;
    player_won      = false;

    player.reset();
    cinematic_manager.reset();

    main_view.reset({ 0, 0, MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT });

    interaction_board.get_sprite().setScale(0.3, 0.3);
    interaction_board.get_sprite().setPosition({ 45, 150 });

    background_map.reset(config.layer_files);
    platform_map.reset(config.level_descriptor_file);

    name_tag        = config.name_tag;
    next_screen_s   = name_tag;
    triggers        = config.triggers;

    cinematic_manager.reset();
}

void Play_Screen::handle_drawing(Renderer &renderer)
{
    renderer.clear();

    renderer.set_view(main_view);

    for (int i = 0; i < background_map.get_layers(); ++i)
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

    if (player_won)
    {
        sf::Font font;
        font.loadFromFile("assets/other/font1.ttf");
        sf::Text reset_text("You made it, Now you can try again next day\n\nYou probably won't make it...", font);
        reset_text.setPosition(main_view.getCenter().x - 50, main_view.getCenter().y - 15);
        reset_text.setCharacterSize(15);
        reset_text.setScale(0.25, 0.25);
        reset_text.setFillColor(sf::Color::Black);

        renderer.draw(reset_text);
    }

    if (player_dying)
    {
        explosion_animation_manager.tick_active_animation();
        renderer.draw(explosion_animation_manager.get_sprite());

        if (explosion_animation_manager.has_active_animation_yielded())
        {
            player_dying = false;
            player_dead = true;
        }
    }
    else if (player_dead)
    {
        sf::Font font;
        font.loadFromFile("assets/other/font1.ttf");
        sf::Text reset_text("You didn't make it...\nPress E to try again", font);
        reset_text.setPosition(main_view.getCenter().x - 25, main_view.getCenter().y - 15);
        reset_text.setCharacterSize(15);
        reset_text.setScale(0.25, 0.25);
        reset_text.setFillColor(sf::Color::Black);

        renderer.draw(reset_text);
        
        if (Keyboard_IO::is_key_pressed(sf::Keyboard::E)) reset(configuration);
    }

    
    if (trigger_on)
    {
        renderer.draw(interaction_board.get_sprite());

        Text text(active_trigger.explanation_text);
        text.get_text().setPosition(48, 151);
        text.get_text().setScale(0.15, 0.15);
        
        renderer.draw(text.get_text());
    }
    
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

void Play_Screen::handle_active_tiles()
{
    auto tile_under_player = cinematic_manager.get_tile_under_player();
    if (tile_under_player == TILE::MINE_BLOCK)
    {
        player_dying = true;
        explosion_animation_manager.add_animation("explosion", "assets/other/explosion.png", 8, 5, main_view.getCenter().x - 25, player.get_absolute_y());
        explosion_animation_manager.set_active_animation("explosion");
    }
    else if (tile_under_player == TILE::FINISH_BLOCK)
    {
        player_won = true;
    }
}

void Play_Screen::handle_frame(Renderer &renderer)
{
    if (!player_dying && !player_dead && !player_won)
    {
        handle_input();
        handle_triggers();
        handle_active_tiles(); //tiles that can perform an action (ie kill the player) are named active
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
