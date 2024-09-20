#pragma once

#include<iostream>
#include <memory>
#include<raylib.h>
#include "window.hpp"
#include<deque>
#include "Dialog.hpp"
#include "TextState.hpp"
#include "Interface.hpp"




class ActionWindow : public Window {
private:
    // Rectangle saveBtn;
    // Rectangle openBtn;
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