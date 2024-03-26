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

    vec2 uv = gl_FragCoord.xy / screen_height;

    float amplitude_real = 0.0;
    float amplitude_imag = 0.0;
    for (int i = 0; i < num_sources; ++i)
    {
        float source_y = (num_sources == 1) ? 0.5 : (0.3 + float(i) / float(num_sources - 1) * 0.4);
        float r = distance(vec2(0.1, source_y), uv);
        float phase_shift = 8.0 * float(i) / float(num_sources - 1);

        amplitude_real += amplitude / r * cos(-k * r + omega * time + phase_shift);
        amplitude_imag += amplitude / r * sin(-k * r + omega * time + phase_shift);
    }

    if (show_intensity == 1)
    {
        float intensity = amplitude_real * amplitude_real + amplitude_imag * amplitude_imag;
        intensity = clamp(10 * intensity / (float(num_sources) * float(num_sources)), 0.0, 1.0);
        color = vec4(intensity, 0.65 * intensity, 0.0, 1.0);
    }
    else
    {
        amplitude_real /= float(num_sources);
        float wave_pos = clamp(amplitude_real, 0.0, 1.0);
        float wave_neg = clamp(-amplitude_real, 0.0, 1.0);
        color = vec4(wave_pos, 0.0, wave_neg, 1.0);
    }
}
