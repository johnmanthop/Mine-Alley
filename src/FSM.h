#ifndef FSM_
#define FSM_

#include <map>
#include <vector>
#include <string>

class FSM
{
private:
    std::string current_state;
public:
    std::map<std::string, std::map<std::string, std::string>> table;
public:
    FSM() { current_state = ""; }

    void force(const std::string &s) { current_state = s; }
    std::string state() const { return current_state; }
    void advance(const std::string &action) { current_state = table[current_state][action]; }
    bool timed() const;
    void construct_default_character_table();
    void construct_default_enemy1_table();
};

#endif