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
    const int phase_shift_loc = GetShaderLocation(shader, "phase_shift");
    const int num_sources_loc = GetShaderLocation(shader, "num_sources");

    float phase_shift = 0.0f;
    int num_sources = 4;
    bool num_sources_editing = false;

    const int ui_width = 250;

    while (!WindowShouldClose())
    {
        const int screen_width = GetScreenWidth();
        const int screen_height = GetScreenHeight();
        const float ui_x = (float)(screen_width - ui_width);

        BeginDrawing();
        ClearBackground(BLACK);

        SetShaderValue(
            shader, screen_height_loc, &screen_height, SHADER_UNIFORM_INT);
        SetShaderValue(
            shader, phase_shift_loc, &phase_shift, SHADER_UNIFORM_FLOAT);
        SetShaderValue(
            shader, num_sources_loc, &num_sources, SHADER_UNIFORM_INT);
        BeginShaderMode(shader);
        DrawRectangle(0, 0, screen_width - ui_width, screen_height, BLACK);
        EndShaderMode();

        DrawFPS(10, 10);

        // TODO: Proper GUI with nice panel for the controls and a GUI-themed
        // border around the simulation view
        GuiSlider((Rectangle) {ui_x + 110, 10, 100, 20},
                  TextFormat("Phase shift: %5.1f°", (double)phase_shift),
                  NULL,
                  &phase_shift,
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

        EndDrawing();
    }

    UnloadShader(shader);

    CloseWindow();

    return 0;
}
