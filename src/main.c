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

    const int screen_width_loc = GetShaderLocation(shader, "screen_width");
    const int screen_height_loc = GetShaderLocation(shader, "screen_height");
    const int angle_loc = GetShaderLocation(shader, "angle");
    const int time_loc = GetShaderLocation(shader, "time");
    const int num_sources_loc = GetShaderLocation(shader, "num_sources");

    float angle = 0.0f;
    int num_sources = 4;

    while (!WindowShouldClose())
    {
        const int screen_width = GetScreenWidth();
        const int screen_height = GetScreenHeight();
        const float time = (float)GetTime();

        SetShaderValue(
            shader, screen_width_loc, &screen_width, SHADER_UNIFORM_INT);
        SetShaderValue(
            shader, screen_height_loc, &screen_height, SHADER_UNIFORM_INT);
        SetShaderValue(shader, angle_loc, &angle, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, time_loc, &time, SHADER_UNIFORM_FLOAT);
        SetShaderValue(
            shader, num_sources_loc, &num_sources, SHADER_UNIFORM_INT);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(shader);
        DrawRectangle(0, 0, screen_width, screen_height, BLACK);
        EndShaderMode();

        GuiLabel((Rectangle) {10, 50, 200, 20}, "A test label");

        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadShader(shader);

    CloseWindow();

    return 0;
}
