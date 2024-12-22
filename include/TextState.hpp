#pragma once
#include<string>
#include<deque>


struct TextState
{
    std::deque<std::string> lines;
    std::string lang_extension;
};