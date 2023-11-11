#ifndef RENDER_INC
#define RENDER_INC

#include <vector>
#include <SFML/Graphics.hpp>
class Renderer
{
private:
    bool is_open;
    sf::RenderWindow window;
public:
    Renderer(int x, int y, std::string title);
public:
    std::vector<sf::Event> get_event_list();
    void close() { is_open = false; window.close(); }
    void clear();
    void display();
    void set_view(const sf::View &view);
    bool is_window_open() const { return is_open; }

    template<typename T>
    void draw(const T &drawable)
    {
        window.draw(drawable);
    }

    const unsigned int width;
    const unsigned int height;
};

#endif
