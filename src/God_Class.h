#ifndef GOD_CLASS_INC
#define GOD_CLASS_INC

#include <memory>

#include "Exposition_Screen.h"
#include "Renderer.h"
#include "Play_Screen.h"
#include "INIReader.h"

class God_Class
{
private:
    std::map<std::string, std::shared_ptr<Screen>> scenes;
    std::string current_screen;
    Renderer renderer;
private:
    Screen_Configuration parse_configuration(const std::string &ini_file) const;
    void process_newline_in_string(std::string &str) const;
public:
    God_Class();
public:
    void main_loop();
};

#endif 