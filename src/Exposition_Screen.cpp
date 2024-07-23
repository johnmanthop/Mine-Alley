#include "Exposition_Screen.h"

Exposition_Screen::Exposition_Screen(const Screen_Configuration &config)
{
    main_view.reset({ { 0, 0 }, { MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT } });

    reset(config);
}

void Exposition_Screen::reset(const Screen_Configuration &config)
{
    name_tag = config.name_tag;
    next_screen_s = name_tag;
    action = config.action;
    log.reset(config.layer_files[0]);
    exposition_text.reset(config.exposition_text, "assets/HUD/font1.ttf");
    exposition_text.get_text().setScale(0.035, 0.035);
    exposition_text.get_text().setPosition(3, 3);
    exposition_text.get_text().setFillColor(sf::Color::Black);
}

void Exposition_Screen::handle_drawing(Renderer &renderer)
{
    renderer.clear();

    renderer.set_view(main_view);
    renderer.draw(log.get_sprite());
    renderer.draw(exposition_text.get_text());

    renderer.display();
}

void Exposition_Screen::handle_input()
{
    if (Keyboard_IO::is_key_pressed_once(sf::Keyboard::E))
    {
        next_screen_s = action;
    }
}

std::string Exposition_Screen::next_screen()
{
    auto to_return = next_screen_s;
    next_screen_s = name_tag;

    return to_return;
}

void Exposition_Screen::handle_frame(Renderer &renderer)
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