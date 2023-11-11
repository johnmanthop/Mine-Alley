#ifndef TEXT
#define TEXT

#include <SFML/Graphics.hpp>
#include <string>

class Text
{
private:
    sf::Text ftext;
    sf::Font font;
public:
    Text() {}
    Text(const std::string &text, const std::string &font_string = "assets/font1.ttf") { reset(text, font_string); }

    void reset(const std::string &text, const std::string &font_string = "assets/font1.ttf")
    {
        font.loadFromFile(font_string);
        ftext.setString(text);
        ftext.setFont(font);
    }

    sf::Text& get_text() { return ftext; }
};


#endif