#include "raylib.h"
#include <string>
#include "Config.hpp"
#include "WindowState.hpp"




int main() {
    int screenWidth = 1280;
    int screenHeight = 720;

    Config::Cfg cfg = Config::parse("cfg.txt");
    SetConfigFlags(ConfigFlags::FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "KText Editor");
    SetExitKey(0);

    WindowContext context(cfg);




    SetTargetFPS(GetMonitorRefreshRate(0));
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F1)) {
            context.switch_page();
        }

        context.update();

        BeginDrawing();
        context.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
