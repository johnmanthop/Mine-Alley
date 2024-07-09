#ifndef SPLASH_SCREEN
#define SPLASH_SCREEN

#include <string>

#include "Keyboard_IO.h"
#include "Drawable_Content.h"
#include "Constants.h"
#include "Screen.h"

class Splash_Screen : public Screen
{
private:
    std::string advance_screen;
    std::string next_screen_s;
    std::string action;
    std::string name_tag;
    Drawable_Static splash;
private:
    void handle_drawing(Renderer &renderer);
    void handle_input();
public:
    Splash_Screen(const Screen_Configuration &config);
    void reset(const Screen_Configuration &config);

    void handle_frame(Renderer &renderer) override;
    std::string next_screen() { return next_screen_s; }
};

#endif 