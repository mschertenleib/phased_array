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
    const int num_sources_loc = GetShaderLocation(shader, "num_sources");
    const int source_spacing_loc = GetShaderLocation(shader, "source_spacing");
    const int wavelength_loc = GetShaderLocation(shader, "wavelength");
    const int phase_shift_loc = GetShaderLocation(shader, "phase_shift");

    int num_sources = 8;
    bool num_sources_editing = false;
    float source_spacing = 0.005f;
    float wavelength = 4.0f * source_spacing;
    float phase_shift = 0.0f;

    GuiSetStyle(DEFAULT, TEXT_SIZE, GuiGetStyle(DEFAULT, TEXT_SIZE) * 2);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, (int)0xc0c0c0ff);

    while (!WindowShouldClose())
    {
        const int screen_width = GetScreenWidth();
        const int screen_height = GetScreenHeight();
        const float ui_x = (float)(screen_width - 150);

        BeginDrawing();
        ClearBackground(BLACK);

        SetShaderValue(
            shader, screen_height_loc, &screen_height, SHADER_UNIFORM_INT);
        SetShaderValue(
            shader, num_sources_loc, &num_sources, SHADER_UNIFORM_INT);
        SetShaderValue(
            shader, source_spacing_loc, &source_spacing, SHADER_UNIFORM_FLOAT);
        SetShaderValue(
            shader, wavelength_loc, &wavelength, SHADER_UNIFORM_FLOAT);
        SetShaderValue(
            shader, phase_shift_loc, &phase_shift, SHADER_UNIFORM_FLOAT);

        BeginShaderMode(shader);
        DrawRectangle(0, 0, screen_width, screen_height, BLACK);
        EndShaderMode();

        if (GuiSpinner((Rectangle) {ui_x, 10, 140, 30},
                       "Number of sources",
                       &num_sources,
                       1,
                       100,
                       num_sources_editing))
        {
            num_sources_editing = !num_sources_editing;
        }
        if (num_sources > 100)
        {
            num_sources = 100;
        }

        GuiSlider((Rectangle) {ui_x, 50, 140, 30},
                  TextFormat("Source spacing: %6.4f", (double)source_spacing),
                  NULL,
                  &source_spacing,
                  0.001f,
                  0.015f);

        GuiSlider((Rectangle) {ui_x, 90, 140, 30},
                  TextFormat("Wavelength: %6.4f", (double)wavelength),
                  NULL,
                  &wavelength,
                  0.005f,
                  0.06f);

        GuiSlider((Rectangle) {ui_x, 130, 140, 30},
                  TextFormat("Phase shift: %6.1f°", (double)phase_shift),
                  NULL,
                  &phase_shift,
                  -180.0f,
                  180.0f);

        EndDrawing();
    }

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
