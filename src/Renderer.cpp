#include "Renderer.h"

Renderer::Renderer(int x, int y, std::string title):
    window(sf::VideoMode(x, y), title),
    width(x), height(y),
    is_open(true)

{
    window.setFramerateLimit(60);
}

void Renderer::clear()
{
    window.clear();
}

void Renderer::display()
{
    window.display();
}

std::vector<sf::Event> Renderer::get_event_list()
{
    sf::Event event;

    std::vector<sf::Event> event_list;
    event_list.reserve(10);

    while (window.pollEvent(event))
    {
        event_list.push_back(event);
    }

    return event_list;
}

void Renderer::set_view(const sf::View &view)
{
    window.setView(view);
}