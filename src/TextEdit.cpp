#include "TextEdit.hpp"
#include "TextState.hpp"
#include <algorithm>
#include <ostream>
#include <ranges>
#include <raylib.h>
#include <string>
#include "print"
const constexpr int startXPos = 45;

TextWindow::TextWindow(std::string font_path, int fontSize, int spacing, TextState &state)
 :  fontSize(fontSize), spacing(spacing), active_line(0), 
cursorX(0), cursor_index(0), scroll_offset(0), scroll_step(3), state(state)
{
    font = LoadFont("../Roboto-Regular.ttf");
    //font = LoadFont(font_path.c_str()); //Setting up a font
    state.lines.push_back("");
}
TextWindow::TextWindow(std::string font_path, int fontSize, int spacing, size_t scroll_step, TextState &state) : TextWindow(font_path, fontSize, spacing, state) {
    this->scroll_step = scroll_step;
}
TextWindow::~TextWindow()
{
    //Delete font
    //UnloadFont(font);
}    

void TextWindow::handle_input()
{
    handle_inserting();
    
    handle_erasing();
   
    handle_arrows_mov();

    handle_scrolling();
}

void TextWindow::handle_erasing() {
    if((IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE)) && cursor_index > 0) {
        state.lines[active_line].erase(cursor_index - 1, 1); //Erasing symbol where cursor x is
        cursor_index--; //Moving cursor to the left

    } else if ((IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE)) && cursor_index == 0 && active_line != 0) {

        cursor_index = state.lines[active_line - 1].size(); //Settings cursor X to the end of the previous line

        state.lines[active_line - 1] += state.lines[active_line]; //Adding current line contents to the previous line
        state.lines.erase(state.lines.begin() + active_line); //Erasing current line

        active_line--; //Changing focus to the previous line (higher)
        //Automatically scrolling up so user doesnt type over the screen
        //std::println("{} {}", (int)active_line - (int)scroll_offset, GetScreenHeight() / textSize.y - 1 - scroll_offset);
        if ((int)active_line - (int)scroll_offset < 0) {
            
            scroll_offset -= scroll_step; //Scroll page a bit so u dont type under the screen
        }
        
    }
}
   
   
void TextWindow::handle_inserting() {
     if(IsKeyPressed(KEY_ENTER))
    {
        //printf("this\n");
        state.lines.insert(state.lines.begin() + active_line + 1, ""); //Inserting a new line for a new line 
        state.lines[active_line + 1] = state.lines[active_line].substr(cursor_index); //Moving the part of the string after current pos on a new line


        state.lines[active_line].erase(cursor_index); //Erasing the previously moved part

        active_line++; //Moving focus to the next line (lower)

        cursor_index = 0; //Setting xpos to a new line

        if (static_cast<int>(active_line - scroll_offset)  > GetScreenHeight() / textSize.y - 1) {
           
            scroll_offset += scroll_step; //Scroll page a bit so u dont type under the screen
        }
       
    }
    
    if (IsKeyPressed(KEY_TAB))
    {
        state.lines[active_line].insert(cursor_index, "    ");
        cursor_index += 4; //Moving cursor to the right
        
    }
    
}

void TextWindow::handle_scrolling() {
    int mouse_move = GetMouseWheelMove();
    
    const size_t text_size = state.lines.size();

    if (text_size > 2) {
        
        if (mouse_move < 0 && (int)scroll_offset + (int)GetScreenHeight() / (int)textSize.y - 1 - (int)text_size <= 35 /*Magic*/) {
            scroll_offset += scroll_step; //Scroll down
        } else if (mouse_move > 0 && scroll_offset >= 1) {
            scroll_offset -= scroll_step; //Scroll up
        }
    }
}

void TextWindow::handle_shortcuts() {
    if(IsKeyPressed(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V))
    {
        std::cout << "Paste" << std::endl;
    }
}


void TextWindow::handle_arrows_mov() {

    if((IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) && cursor_index > 0)
    {
        //If the cursor is at the beginning condition fails
        cursor_index--;
    } else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) && cursor_index == 0 && active_line != 0) 
    {
        active_line--; //Changing focus to a line higher
        cursor_index = state.lines[active_line].size(); //Moving cursor to the end of the line
        //cursorY -= textSize.y; //Moving cursor higher
    }
    
    
    if((IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) && cursor_index < static_cast<int>(state.lines[active_line].size()))
    {
        cursor_index++;
    } else if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) && active_line + 1 != state.lines.size())
    {
        active_line++; //Changing focus to a line higher
        cursor_index = 0; //Moving cursor to the beginning of the line
        //cursorY += textSize.y;  //Moving cursor lower
    }
    
    if(IsKeyPressed(KEY_UP) && active_line >= 1) //textsize y is the first line 
    {
        //cursorY -= textSize.y; //Moving cursor UP
        active_line--; //Changing focused string line

        if(cursor_index >= static_cast<int>(state.lines[active_line].size())) //So it won't go out of range
        {
            cursor_index = state.lines[active_line].size();
        }
        
    }
    else if(IsKeyPressed(KEY_DOWN) && active_line < state.lines.size() - 1)
    {
        active_line++; //Changing focused string line

        if(cursor_index >= static_cast<int>(state.lines[active_line].size()))  //So it won't go out of range
        {
            cursor_index = state.lines[active_line].size();
        }
    }


}


void TextWindow::text_input_handle()
{
    char ch = GetCharPressed(); //Getting key that was pressed including symbols like @

    if(ch != 0)
    {   
        state.lines[active_line].insert(cursor_index, 1, ch); //Inserting character where the cursor is
        cursor_index += 1; //Moving cursor to the right
    }
}

void TextWindow::Update()
{
    

    textSize = MeasureTextEx(font, "l", fontSize, spacing); // Measure the text size
    textSize.x = startXPos; //Init textSize
    for(int i = 0; i < cursor_index; ++i) //MMoving cursor on X axis until its at cursor_index location (This way the cursor isn't offset and etc, its exactly at a char location)
    {
        
        textSize.x += MeasureTextEx(font, std::string(1, state.lines[active_line][i]).c_str(), fontSize, spacing).x + spacing;
    }

    handle_input();
    
    text_input_handle();


    cursorX = textSize.x;
}

void TextWindow::draw_lines_cnt() {
    //Drawing line count
    for(size_t i = 0; i < state.lines.size(); ++i)
    {
        int line_actual = i + scroll_offset; //Line regardless of scrolling (so the position is correct)
        if (line_actual < static_cast<int>(state.lines.size())) {
            DrawTextEx(font, std::to_string(i + scroll_offset).c_str(), { static_cast<float>((float)startXPos / 6), i * textSize.y}, fontSize - 3, spacing, LIGHTGRAY);

            if (i + scroll_offset == active_line) { //If the current drawn line is the focused line, draw cursor
                DrawRectangle(cursorX, i * textSize.y, 3, textSize.y, LIGHTGRAY);
            }
        }
    }
}

void TextWindow::draw_text() {
    for(size_t i = scroll_offset; i < state.lines.size(); ++i) //Drawing all lines of text 
    {
        float size_already{startXPos};

        auto words = std::views::split(state.lines[i], ' ') 
        | std::views::transform([](auto &&rng) {
            auto result = std::string(rng.begin(), rng.end());
            result += " ";
            return result;
        })
        | std::ranges::to<std::vector<std::string>>(); // Spliting words


        auto words_and_colors = SyntaxHighlight::parse_line(words);

        for (const auto &[word, color] : words_and_colors) {
            DrawTextEx(font, word.c_str(), 
            { size_already , (i - scroll_offset) * textSize.y}, //Figuring out actual position
            fontSize, spacing, color);

            size_already += MeasureTextEx(font, word.c_str(), fontSize, spacing).x + spacing;
        }

        // for (auto word : words) {
            
            
        //     DrawTextEx(font, word.c_str(), 
        //     { size_already , (i - scroll_offset) * textSize.y}, //Figuring out actual position
        //     fontSize, spacing, syntax_color(word));

        //     size_already += MeasureTextEx(font, word.c_str(), fontSize, spacing).x + spacing;
        // }
    
    }
}

void TextWindow::Draw()
{

    ClearBackground(DARKGRAY);

    draw_lines_cnt();
    draw_text();
}



