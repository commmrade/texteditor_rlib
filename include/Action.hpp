#pragma once

#include <memory>
#include<raylib.h>
#include "window.hpp"
#include "TextState.hpp"
#include "Interface.hpp"




class ActionWindow : public Window {
private:
 
    std::unique_ptr<Box> box;
    TextState &state;
public:
    ActionWindow(TextState &state);
    ActionWindow() = delete;

    ActionWindow(const ActionWindow &other) = delete;
    ActionWindow(ActionWindow &&other) = delete;

    ~ActionWindow();


    void Update();
    void Draw();
};