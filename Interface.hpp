#include<raylib.h>
#include<string>
#include<deque>
#include<iostream>

struct Button {
    Rectangle button;
    std::string label;

    Button(std::string label_name) {
        label = label_name;
    } 

    Button(int sizeX, int sizeY, std::string label_name) : Button(label_name) {
        button.height = sizeY;
        button.width = sizeX;
    } 
};


class Box {
private:
    int button_size_real;
    int spacing;

    float x_del; //x starting point
    float y_del; //y starting point

    std::deque<Button> buttons;
public:
    Box(float layout_x, float layout_y) {
        this->x_del = layout_x;
        this->y_del = layout_y;
    }

    void set_size(int size) {
        button_size_real = size;
    }
    void set_spacing(int spacing) {
        this->spacing = spacing;
    }

    void add_button(Button &but) {
        buttons.push_back(but);
    }

    void draw_buttons() {
        float button_size_x = button_size_real * ((float)GetScreenWidth() / (float)GetScreenHeight());
        float button_size_y = button_size_real * ((float)GetScreenHeight() / (float)GetScreenWidth()) * 1.5; //Setting button size

        auto step = button_size_y + spacing; //for calculating position for buttons
        float layout_x = GetScreenWidth() / x_del;
        float layout_y = GetScreenHeight() / y_del;

        for (size_t i = 0; i < buttons.size(); i++) {
            
            auto &button = buttons[i];

            button.button.x = layout_x;
            button.button.y = layout_y + (step * i); //Setting pos for button

            button.button.width = button_size_x * 2; //Setting size for button
            button.button.height = button_size_y;
            
            DrawRectangleRec(button.button, LIGHTGRAY);
            DrawText(button.label.c_str(), button.button.x + (static_cast<float>(button_size_x) / 2), button.button.y + (static_cast<float>(button_size_y) / 4), ((button_size_x + button_size_y) / (GetScreenWidth() / GetScreenHeight())) / 8, BLACK);
        }
    }

    auto &get_buttons() {
        return buttons;
    }

};