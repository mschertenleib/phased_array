#version 330

out vec4 color;

uniform int screen_width;
uniform int screen_height;
uniform int show_intensity;
uniform float angle;
uniform float time;
uniform int num_sources;

void main()
{
    const float k = 200.0;
    const float omega = 10.0;
    const float amplitude = 0.1;

    vec2 uv = gl_FragCoord.xy / vec2(screen_width, screen_height);

    float field = 0.0;
    for (int i = 0; i < num_sources; ++i)
    {
        float source_y = (num_sources == 1) ? 0.5 : (0.3 + float(i) / float(num_sources - 1) * 0.4);
        float r = distance(vec2(0.1, source_y), uv);
        field += amplitude / r * cos(k * r - omega * time);
    }

    field /= float(num_sources);

    if (show_intensity == 1)
    {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        color = vec4(clamp(field, 0.0, 1.0), 0.0, clamp(-field, 0.0, 1.0), 1.0);
    }
}
