#include<iostream>
#include<fstream>

class Config
{
public:
    struct Cfg
    {
        int fontSize = 20;
        int spacing = 3;
        std::string fontPath;
        int scroll_step = 3;
    };
    
    static Cfg parse(const std::string &path);

};