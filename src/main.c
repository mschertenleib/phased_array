#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else
#define GLSL_VERSION 100
#endif

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Phased Array");

    const Shader shader =
        LoadShader(0, TextFormat("src/shader.frag", GLSL_VERSION));

    const int screen_height_loc = GetShaderLocation(shader, "screen_height");
    const int angle_loc = GetShaderLocation(shader, "angle");
    const int num_sources_loc = GetShaderLocation(shader, "num_sources");

    float angle = 0.0f;
    int num_sources = 4;
    int num_sources_editing = false;

    const int ui_width = 250;

    while (!WindowShouldClose())
    {
        const int screen_width = GetScreenWidth();
        const int screen_height = GetScreenHeight();
        const float ui_x = (float)(screen_width - ui_width);

        SetShaderValue(
            shader, screen_height_loc, &screen_height, SHADER_UNIFORM_INT);
        SetShaderValue(shader, angle_loc, &angle, SHADER_UNIFORM_FLOAT);
        SetShaderValue(
            shader, num_sources_loc, &num_sources, SHADER_UNIFORM_INT);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(shader);
        DrawRectangle(0, 0, screen_width - ui_width, screen_height, BLACK);
        EndShaderMode();

        // TODO: Proper GUI with nice panel for the controls and a GUI-themed
        // border around the simulation view
        GuiSlider((Rectangle) {ui_x + 110, 10, 100, 20},
                  TextFormat("Angle: %5.1f", (double)angle),
                  NULL,
                  &angle,
                  -90.0f,
                  90.0f);

        if (GuiSpinner((Rectangle) {ui_x + 110, 40, 100, 20},
                       "Sources",
                       &num_sources,
                       1,
                       100,
                       num_sources_editing))
        {
            num_sources_editing = !num_sources_editing;
        }
        if (num_sources < 1)
        {
            num_sources = 1;
        }
        else if (num_sources > 100)
        {
            num_sources = 100;
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadShader(shader);

    CloseWindow();

    return 0;
}
