#version 330

out vec4 color;

uniform int screen_height;
uniform float angle;
uniform int num_sources;

void main()
{
    const float k = 200.0;
    const float omega = 10.0;
    const float amplitude = 0.2;

    vec2 xy = gl_FragCoord.xy / screen_height;

    float amplitude_real = 0.0;
    float amplitude_imag = 0.0;
    for (int i = 0; i < num_sources; ++i)
    {
        float source_y = (num_sources == 1) ? 0.5 : (0.35 + float(i) / float(num_sources - 1) * 0.3);
        float r = distance(vec2(0.1, source_y), xy);
        float phase_shift = (num_sources == 1) ? 0.0 : 8.0 * float(i) / float(num_sources - 1);

        amplitude_real += amplitude / r * cos(-k * r + phase_shift);
        amplitude_imag += amplitude / r * sin(-k * r + phase_shift);
    }

    float wave_pos = sqrt(clamp(amplitude_real / float(num_sources), 0.0, 1.0));
    float wave_neg = sqrt(clamp(-amplitude_real / float(num_sources), 0.0, 1.0));
    color = vec4(wave_pos, 0.6 * wave_pos + 0.4 * wave_neg, wave_neg, 1.0);
}
