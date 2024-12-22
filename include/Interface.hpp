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
    Box(float layout_x, float layout_y);

    void set_size(int size);
    void set_spacing(int spacing);
    void add_button(const Button &but);

    void draw_buttons();

    auto get_buttons() const {
        return buttons;
    }

};