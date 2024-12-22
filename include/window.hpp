#pragma once

class Window {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0; 

    Window() = default;
    Window(const Window &) = delete;
    Window(Window &&) = delete;
    Window& operator=(const Window &) = delete; 
    Window& operator=(Window &&) = delete;

    virtual ~Window() {}
};


