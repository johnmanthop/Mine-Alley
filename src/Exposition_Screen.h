#ifndef EXPOSITION_SCREEN
#define EXPOSITION_SCREEN

#include "Constants.h"
#include "Text.h"
#include "Screen.h"
#include "Drawable_Content.h"

class Exposition_Screen : public Screen
{
private:
    Text exposition_text;
    Drawable_Static log;
    std::string next_screen_s;
    std::string action;
    std::string name_tag;
private:
    void handle_drawing(Renderer &renderer);
    void handle_input();
    void reset(const Screen_Configuration &config);
public:
    Exposition_Screen(const Screen_Configuration &config);
    void handle_frame(Renderer &renderer) override;
    void set_exposition_text(const std::string &exposition_text_) { exposition_text = exposition_text_; }
    std::string next_screen() override;
};

#endif