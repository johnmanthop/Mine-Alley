#include "Splash_Screen.h"

Splash_Screen::Splash_Screen(const Screen_Configuration &config)
{
    reset(config);
}

void Splash_Screen::reset(const Screen_Configuration &config)
{
    main_view.reset({ { 0, 0 }, { MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT } });

    advance_screen = config.action;
    splash.reset(config.layer_files[0]);
    name_tag = config.name_tag;
    next_screen_s = name_tag;
}

void Splash_Screen::handle_input()
{
    if (Keyboard_IO::is_key_pressed(sf::Keyboard::E))
    {
        next_screen_s = advance_screen;
    }
}

void Splash_Screen::handle_drawing(Renderer &renderer)
{
    renderer.clear();

    renderer.set_view(main_view);
    renderer.draw(splash.get_sprite());
    
    renderer.display();
}

void Splash_Screen::handle_frame(Renderer &renderer)
{
    handle_input();

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