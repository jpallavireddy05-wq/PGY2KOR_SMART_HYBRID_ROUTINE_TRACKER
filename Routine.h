#pragma once
#include <string>

class Routine {
public:
    int id{};
    std::string title;
    std::string category;
    std::string priority;
    bool completed{false};

    Routine();  
};
