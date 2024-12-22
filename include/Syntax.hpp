

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

    static std::vector<Token> parse_line(const std::vector<std::string> &words, std::string lang = "") {
        std::vector<Token> result;


        
        if (auto cpp_map = lang_keywords.find(lang); lang == "cpp" && cpp_map != lang_keywords.end()) {
            
            
            for (auto word : words) {
                trim_r(word);

                auto word_color = cpp_map->second.find(word);
                if (word_color == cpp_map->second.end()) {
                    
                    result.push_back({word + " ", WHITE});
                } else {
                    
                    result.push_back({word + " ", word_color->second});
                }

            }
        } else if (auto lang_map = lang_keywords.find(lang); lang == "py" && lang_map != lang_keywords.end()) {
        
            
            for (auto word : words) {
                std::cout << word << std::endl;
                trim_r(word);

                auto word_color = lang_map->second.find(word);
                if (word_color == lang_map->second.end()) {
                    
                    result.push_back({word + " ", WHITE});
                } else {
                    
                    result.push_back({word + " ", word_color->second});
                }

            }
        } else {
            
            for (auto word : words) {
                trim_r(word);
                result.push_back({word + " ", WHITE});
            }
        }
       
        return result;
    }

private:
   static inline const std::unordered_map<std::string, std::unordered_map<std::string, Color>> lang_keywords = {
    {"cpp", {
        // Data types
        {"int", BLUE},
        {"float", BLUE},
        {"double", BLUE},
        {"char", BLUE},
        {"bool", BLUE},
        {"void", BLUE},
        {"std::string", GREEN},
        {"string", GREEN},
        {"long", BLUE},
        {"short", BLUE},
        {"unsigned", BLUE},
        {"signed", BLUE},

        // Control flow keywords
        {"if", PURPLE},
        {"else", PURPLE},
        {"switch", PURPLE},
        {"case", PURPLE},
        {"for", PURPLE},
        {"while", PURPLE},
        {"do", PURPLE},
        {"break", PURPLE},
        {"continue", PURPLE},
        {"return", PURPLE},
        {"goto", PURPLE},

        // Access modifiers
        {"public", ORANGE},
        {"private", ORANGE},
        {"protected", ORANGE},

        // Memory management
        {"new", YELLOW},
        {"delete", YELLOW},

        // C++ features
        {"class", SKYBLUE},
        {"struct", SKYBLUE},
        {"namespace", SKYBLUE},
        {"using", SKYBLUE},
        {"template", SKYBLUE},
        {"typename", SKYBLUE},
        {"auto", SKYBLUE},
        {"const", SKYBLUE},
        {"constexpr", SKYBLUE},
        {"static", SKYBLUE},
        {"inline", SKYBLUE},
        {"virtual", SKYBLUE},
        {"override", SKYBLUE},
        {"mutable", SKYBLUE},

        // Operators
        {"sizeof", RED},
        {"typeid", RED},
        {"dynamic_cast", RED},
        {"static_cast", RED},
        {"reinterpret_cast", RED},
        {"const_cast", RED},
        
        // Boolean literals
        {"true", DARKGREEN},
        {"false", DARKGREEN},

        // Null pointer
        {"nullptr", GRAY},

        // Preprocessor
        {"#include", LIGHTGRAY},
        {"#define", LIGHTGRAY},
        {"#if", LIGHTGRAY},
        {"#ifdef", LIGHTGRAY},
        {"#ifndef", LIGHTGRAY},
        {"#else", LIGHTGRAY},
        {"#elif", LIGHTGRAY},
        {"#endif", LIGHTGRAY},
        {"#pragma", LIGHTGRAY}
    }},
    {"py", {
        // Data types
        {"int", BLUE},
        {"float", BLUE},
        {"str", GREEN},
        {"list", GREEN},
        {"dict", GREEN},
        {"set", GREEN},
        {"tuple", GREEN},
        {"bool", BLUE},

        // Control flow keywords
        {"if", PURPLE},
        {"elif", PURPLE},
        {"else", PURPLE},
        {"for", PURPLE},
        {"while", PURPLE},
        {"break", PURPLE},
        {"continue", PURPLE},
        {"return", PURPLE},
        {"pass", PURPLE},

        // Functions and classes
        {"def", SKYBLUE},
        {"class", SKYBLUE},
        {"lambda", SKYBLUE},

        // Special keywords
        {"import", ORANGE},
        {"from", ORANGE},
        {"as", ORANGE},

        // Operators
        {"and", RED},
        {"or", RED},
        {"not", RED},
        {"in", RED},
        {"is", RED},

        // Boolean literals
        {"True", DARKGREEN},
        {"False", DARKGREEN},

        // NoneType
        {"None", GRAY},

        // Context managers
        {"with", PURPLE},
        {"yield", SKYBLUE},
        {"async", SKYBLUE},
        {"await", SKYBLUE}
    }}
};

};