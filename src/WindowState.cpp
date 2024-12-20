#include "WindowState.hpp"



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