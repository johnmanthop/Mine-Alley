#ifndef SCREEN
#define SCREEN

#include <string>
#include <vector>

#include "Keyboard_IO.h"
#include "Renderer.h"
#include "Trigger.h"

struct Screen_Configuration
{
    std::string name_tag;
    std::vector<std::string> layer_files;
    std::string level_descriptor_file;
    std::string action;
    std::string exposition_text;
    std::vector<Trigger> triggers;
};

struct Screen
{
protected:
    sf::View main_view;
public:
    virtual void handle_frame(Renderer &renderer) = 0;
    virtual std::string next_screen() = 0;
};

#endif