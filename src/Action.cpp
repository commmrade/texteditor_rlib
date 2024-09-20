#include "Action.hpp"
#include "Dialog.hpp"
#include <deque>
#include <memory>
#include <raylib.h>



ActionWindow::ActionWindow(TextState &state) : state(state)
{
    box = std::make_unique<Box>(2.4, 5.0);
    box->set_size(100);
    box->set_spacing(50);

   
    Button open{"Open"};
    Button save{"Save"};

    box->add_button(open);
    box->add_button(save);
}
ActionWindow::~ActionWindow()
{
    //delete main;
}



void ActionWindow::Update()
{
    //auto main = new Main(state);
    std::unique_ptr<Main> main = std::make_unique<Main>(Main(state));
    for (auto &button : box->get_buttons()) {
        if (CheckCollisionPointRec(GetMousePosition(), button.button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (button.label == "Save") {
                main->saveFile();
            } else if (button.label == "Open") {
                main->openFile();
            } else {
                std::cerr << "No button yet\n";
            }
        }        
    }
    //delete main;
    
}
void ActionWindow::Draw()
{
    ClearBackground(DARKGRAY);

    box->draw_buttons();
}
