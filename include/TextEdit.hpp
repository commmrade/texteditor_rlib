#pragma once
#include<iostream>
#include "window.hpp"
#include<deque>
#include<raylib.h>
#include "TextState.hpp"

class TextWindow : public Window {
private:
    int fontSize;
    int spacing;
    
    Font font;

    size_t active_line; //Line that is in focus right now

    int cursorX; //X-cursor location pixel wise
    //int cursorY; //Y cursor location pixel wise

    int cursor_index; //Horizontal index (where cursor is located char-count wise, not  pixel wise)


    size_t scroll_offset; // For Scrolling
    size_t scroll_step;


    Vector2 textSize; 

    TextState &state;

    //Getters, settetrs
    auto get_scroll_step() const { return scroll_step; }
    void set_scroll_step(size_t scroll_step) { this-> scroll_step = scroll_step; }

public:
    //std::deque<std::string> lines{""};
    TextWindow() = delete;
    TextWindow(std::string font_path, int fontSize, int spacing, TextState &state);
    TextWindow(std::string font_path, int fontSize, int spacing, size_t scroll_step, TextState &state);

    TextWindow(const TextWindow& other) = delete;
    TextWindow(TextWindow &&moved) = delete;



    ~TextWindow();

    void Update(); //Updating variables code
    void Draw(); //Drawginc code

    void handle_input();
    void handle_scrolling();
    void handle_shortcuts();
    void text_input_handle();
};
