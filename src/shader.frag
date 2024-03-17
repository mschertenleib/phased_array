#version 330

out vec4 color;

uniform int screen_width;
uniform int screen_height;
uniform vec2 angle;

void main()
{
    float u = gl_FragCoord.x / screen_width;
    float v = gl_FragCoord.y / screen_height;
    color = vec4(u, v, 0.0f, 1.0f);
}
