#include "WindowState.hpp"




WindowContext::WindowContext(const Config::Cfg& cfg) {
    state.lines = {};
    textEditorWindow = std::make_shared<TextWindow>(cfg.fontPath, cfg.fontSize, cfg.spacing, cfg.scroll_step, state);
    actionWindow = std::make_shared<ActionWindow>(state);

    currentState = std::make_unique<TextEditorState>();
}


void WindowContext::set_state(std::unique_ptr<WindowState> newState) {
    currentState = std::move(newState);
}

void WindowContext::update() {
    currentState->update(*this);
}

void WindowContext::draw() {
    currentState->draw(*this);
}

void WindowContext::switch_page() {
    currentState->switch_page(*this);
}



void TextEditorState::update(WindowContext& context) {
    context.get_text_editor_window()->Update();
}

void TextEditorState::draw(WindowContext& context) {
    context.get_text_editor_window()->Draw();
}

void TextEditorState::switch_page(WindowContext& context) {
    context.set_state(std::make_unique<ActionWindowState>());
}


void ActionWindowState::update(WindowContext& context) {
    context.get_action_window()->Update();
}

void ActionWindowState::draw(WindowContext& context) {
    context.get_action_window()->Draw();
}

void ActionWindowState::switch_page(WindowContext& context) {
    context.set_state(std::make_unique<TextEditorState>());
}