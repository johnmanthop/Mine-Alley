#ifndef TRIGGER
#define TRIGGER

#include <string>
#include <functional>

struct Trigger
{
    int position;
    bool is_blocking;
    std::string explanation_text;
    std::string action;
};

#endif