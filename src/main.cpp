
#include "raylib.h"
#include<deque>
#include <memory>
#include <string>
#include <vector>
#include "TextEdit.hpp"
#include "Action.hpp"
#include "TextState.hpp"
#include"Config.hpp"


enum Pages {
    EDITOR,
    ACTION
};





int main(/*int argc, char**argv*/) {
    // Initialization

    Pages page = Pages::EDITOR;

    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    Config::Cfg cfg = Config::parse("cfg.txt");    
    SetConfigFlags(ConfigFlags::FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "KText Editor");
    SetExitKey(0);

    TextState state;
    state.lines = {};

    std::vector<std::unique_ptr<Window>> windows;
    windows.emplace_back(new TextWindow(cfg.fontPath, cfg.fontSize, cfg.spacing, cfg.scroll_step,state));
    windows.emplace_back(new ActionWindow(state));
    

    SetTargetFPS(GetMonitorRefreshRate(0));  
    // Main game loop
    while (!WindowShouldClose()) {  
        
        if(IsKeyPressed(KEY_F1)) {
            page = EDITOR;
        } else if(IsKeyPressed(KEY_F2)) {
            page = ACTION;
        }
        windows[page]->Update();


        BeginDrawing();
        windows[page]->Draw();      
        EndDrawing();
    }
    
    CloseWindow(); 
 
    return 0;
}
