#pragma once 


#include "Action.hpp"
#include "TextEdit.hpp"
#include <memory>
#include "Config.hpp"

class WindowState {
public:
    virtual ~WindowState() = default;
    virtual void update(class WindowContext& context) = 0;
    virtual void draw(class WindowContext& context) = 0;
    virtual void switch_page(class WindowContext& context) = 0;
};

class TextEditorState : public WindowState {
public:
    void update(WindowContext& context) override;

    void draw(WindowContext& context) override;

    void switch_page(WindowContext& context) override;
};


class ActionWindowState : public WindowState {
public:
    void update(WindowContext& context) override;

    void draw(WindowContext& context) override;

    void switch_page(WindowContext& context) override;
};


class WindowContext {
private:
    std::unique_ptr<WindowState> currentState;
    std::shared_ptr<TextWindow> textEditorWindow;
    std::shared_ptr<ActionWindow> actionWindow;

    TextState state;

public:
    WindowContext(const Config::Cfg& cfg);
    WindowContext() = delete;
    WindowContext(const WindowContext&) = delete;
    WindowContext(WindowContext&&) = delete;
    WindowContext& operator=(const WindowContext&) = delete;
    WindowContext& operator=(WindowContext &&) = delete;


    TextWindow* get_text_editor_window() { return textEditorWindow.get(); }
    ActionWindow* get_action_window() { return actionWindow.get(); }

    void set_state(std::unique_ptr<WindowState> newState);

    void update();

    void draw();

    void switch_page();
};
