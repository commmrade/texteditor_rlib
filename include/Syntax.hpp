

#include <cassert>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "Utils.hpp"
#include<iostream>


struct Token {
    std::string word;
    Color color;
};



class SyntaxHighlight {
public:

    static std::vector<Token> parse_line(const std::vector<std::string> &words, std::string lang);

private:
   static const std::unordered_map<std::string, std::unordered_map<std::string, Color>> lang_keywords;

};