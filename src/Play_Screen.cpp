#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Play_Screen.h"
#include "Constants.h"

Play_Screen::Play_Screen(const Screen_Configuration &config):
    //interaction_board("assets/other/board.png"),
    cinematic_manager(player, enemies, background_map, platform_map),
    enemy_ai_manager(player, enemies),
    player(PLAYER_POS_X, PLAYER_POS_Y)
{
    configuration = config;
    reset(configuration);
}

void Play_Screen::reset(const Screen_Configuration &config)
{
    enemies.clear();
    
    for (int i = 0; i < NO_ENEMIES; ++i)
    {
        int x_pos = 2 * ENEMY_POS_X + i * 70;

        enemies.emplace_back(x_pos, ENEMY_POS_Y);
        enemies[i].set_height(1);
        enemies[i].set_height_finetune(0);        

        enemies[i].animation_manager.add_animation("idle_left", "assets/Mob/Boar/Idle/Idle-Sheet.png", 4, 10, x_pos, ENEMY_POS_Y);
        enemies[i].animation_manager.add_animation("walking_left", "assets/Mob/Boar/Walk/Walk-Base-Sheet.png", 6, 10, x_pos, ENEMY_POS_Y);
        enemies[i].animation_manager.add_animation("walking_right", "assets/Mob/Boar/Walk/Walk-Base-Sheet.png", 6, 10, x_pos, ENEMY_POS_Y);
        enemies[i].animation_manager.add_animation("hit_left", "assets/Mob/Boar/Hit-Vanish/Hit-Sheet.png", 4, 5, x_pos, ENEMY_POS_Y);
        enemies[i].animation_manager.add_animation("hit_right", "assets/Mob/Boar/Hit-Vanish/Hit-Sheet.png", 4, 5, x_pos, ENEMY_POS_Y);


        enemies[i].animation_manager.animation_mirror("hit_right", true);
        enemies[i].animation_manager.animation_mirror("walking_right", true);

        FSM fsm_en;
        fsm_en.construct_default_enemy1_table();
        enemies[i].animation_manager.set_animation_fsm(fsm_en);
    }

    player.set_height(2);
    player.set_height_finetune(0);

    player.animation_manager.add_animation("idle_right", "assets/Character/Idle/Idle-Sheet.png", 4, 10, PLAYER_POS_X, PLAYER_POS_Y);
    player.animation_manager.add_animation("idle_left", "assets/Character/Idle/Idle-Sheet.png", 4, 10, PLAYER_POS_X, PLAYER_POS_Y);
    player.animation_manager.add_animation("walking_right", "assets/Character/Run/Run-Sheet.png", 8, 8, PLAYER_POS_X, PLAYER_POS_Y);
    player.animation_manager.add_animation("walking_left", "assets/Character/Run/Run-Sheet.png", 8, 8, PLAYER_POS_X, 95);
    player.animation_manager.add_animation("attacking_right", "assets/Character/Attack-01/Attack-01-Sheet.png", 8, 2, PLAYER_POS_X, PLAYER_POS_Y);
    player.animation_manager.add_animation("attacking_left", "assets/Character/Attack-01/Attack-01-Sheet.png", 8, 2, PLAYER_POS_X, PLAYER_POS_Y);
    
    player.animation_manager.animation_mirror("idle_left", true);
    player.animation_manager.animation_mirror("walking_left", true);
    player.animation_manager.animation_mirror("attacking_left", true);

    FSM fsm;
    fsm.construct_default_character_table();

    player.animation_manager.set_animation_fsm(fsm);

    main_view.reset({ 0, 0, MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT });

    //interaction_board.get_sprite().setScale(0.3, 0.3);
    //interaction_board.get_sprite().setPosition({ 45, 150 });

    background_map.reset(config.layer_files);
    platform_map.reset(config.level_descriptor_file, "assets/Misc/Tiles.png");

    name_tag        = config.name_tag;
    next_screen_s   = name_tag;
    triggers        = config.triggers;

    cinematic_manager.reset();
}

void Play_Screen::handle_drawing(Renderer &renderer)
{
    renderer.clear();

    renderer.set_view(main_view);

    for (int i = 0; i < background_map.get_layer_no(); ++i)
    {
        renderer.draw(background_map.get_sprite(i));
    }

    for (int h = 0; h < platform_map.get_height(); ++h)
    {
        for (int w = 0; w < platform_map.get_width(); ++w)
        {
            renderer.draw(platform_map.get_sprite(w, h));
        }
    }
    
    for (auto &en: enemies)
    {
        renderer.draw(en.get_sprite());
        renderer.draw(en.get_hp_bar_sprite());
    }

    renderer.draw(player.get_sprite());
    renderer.draw(player.get_hp_bar_sprite());
    
    renderer.display();
}

void Play_Screen::handle_enemies()
{
    auto action_list = enemy_ai_manager.tick();
    cinematic_manager.handle_enemies(action_list);
}

void Play_Screen::handle_input()
{
    cinematic_manager.handle_input();
}

void Play_Screen::handle_action(const std::string &action)
{
    if (action == "to_scene1")
    {
        next_screen_s = "scene1";
    }
    else if (action == "to_scene2")
    {
        next_screen_s = "scene2";
    }
    else if (action == "to_scene3")
    {
        next_screen_s = "scene3";
    }
    else if (action == "to_scene3a")
    {
        next_screen_s = "scene3a";
    }
    else if (action == "to_exp1")
    {
        next_screen_s = "exp1";
    }
}

std::string Play_Screen::next_screen()
{
    auto to_return = next_screen_s;
    next_screen_s = name_tag;

    return to_return;
}

void Play_Screen::handle_triggers()
{
    /*
    trigger_on = false;
    for (auto &trigger: triggers)
    {
        if (player.is_in_proximity(trigger.position))
        {
            active_trigger = trigger;
            trigger_on = true;
            if (Keyboard_IO::is_key_pressed_once(sf::Keyboard::E))
            {
                handle_action(trigger.action);
            }
        }
    }
    */
}

void Play_Screen::handle_frame(Renderer &renderer)
{

    handle_input();
    handle_enemies();
    handle_triggers();
    cinematic_manager.tick_gravity();

    

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
