#pragma once
#include<iostream>



class Window {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0; 

    Window() = default;
    Window(const Window &other) = delete;
    Window& operator=(const Window &other) = delete; 

    virtual ~Window() {}
};


