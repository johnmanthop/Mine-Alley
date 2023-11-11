#include <iostream>

#include "God_Class.h"

God_Class::God_Class():
    renderer(1500, 1000, "Mine Alley")
{
    current_screen = "scene0";
    scenes["scene0"] = std::make_shared<Exposition_Screen>  (parse_configuration("configs/intro_scene.ini"));
    scenes["scene1"] = std::make_shared<Play_Screen>        (parse_configuration("configs/scene1.ini"));

}

void God_Class::main_loop()
{
    while (renderer.is_window_open())
    {
        scenes[current_screen]->handle_frame(renderer);
        current_screen = scenes[current_screen]->next_screen();
    }
}

void God_Class::process_newline_in_string(std::string &str) const
{
    for (auto &c: str)
    {
        if (c == ']')
        {
            c = '\n';
        }
    }
}

Screen_Configuration God_Class::parse_configuration(const std::string &ini_file) const
{
    Screen_Configuration configuration;
    INIReader reader(ini_file);
    if (reader.ParseError())
    {
        std::cout << "Configuration Parse Error\n";
    }

    configuration.name_tag = reader.Get("information", "name_tag", "not_found");
    if (configuration.name_tag == "not_found")
    {
        std::cout << "Configuration Parse Error\n";
    }

    configuration.action = reader.Get("information", "action", "no_action");

    int no_of_layers = reader.GetInteger("filepaths", "no_of_layers", -1);
    if (no_of_layers == -1)
    {
        std::cout << "Configuration Parse Error\n";
    }

    configuration.level_descriptor_file = reader.Get("filepaths", "descriptor", "not_found");

    for (int i = 0; i < no_of_layers; ++i)
    {
        std::string current_layer = std::string("l") + std::to_string(i);

        std::string path = reader.Get("filepaths", current_layer, "not_found");
        if (path == "not_found")
        {
            std::cout << "Configuration Parse Error\n";
        }

        configuration.layer_files.push_back(path);
    }

    int no_of_triggers = reader.GetInteger("triggers", "no_of_triggers", -1);
    if (no_of_triggers == -1)
    {
        std::cout << "Configuration Parse Error\n";
    }

    for (int i = 0; i < no_of_triggers; ++i)
    {
        std::string current_trigger = std::string("trigger") + std::to_string(i);
        
        int position = reader.GetInteger(current_trigger, "position", -1);
        if (position == -1)
        {
            std::cout << "Configuration Parse Error\n";
        }

        int is_blocking = reader.GetInteger(current_trigger, "is_blocking", -1);
        if (is_blocking == -1)
        {
            std::cout << "Configuration Parse Error\n";
        }

        std::string explanation_text = reader.Get(current_trigger, "explanation_text", "not_found");
        if (explanation_text == "not_found")
        {
            std::cout << "Configuration Parse Error\n";
        }

        std::string action = reader.Get(current_trigger, "action", "not_found");
        if (action == "not_found")
        {
            std::cout << "Configuration Parse Error\n";
        }

        Trigger trigger;
        trigger.position = position;
        trigger.explanation_text = explanation_text;
        trigger.is_blocking = is_blocking;
        trigger.action = action;

        configuration.triggers.push_back(trigger);
    }

    auto sections = reader.Sections();

    if (sections.count("exposition"))
    {
        std::string exp_text = reader.Get("exposition", "text", "not_found");
        
        process_newline_in_string(exp_text);

        if (exp_text == "not_found")
        {
            std::cout << "Configuration Parse Error\n";
        }

        configuration.exposition_text = exp_text;
    }



    return configuration;
}
