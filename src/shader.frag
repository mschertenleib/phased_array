#version 330

out vec4 color;

uniform int screen_height;
uniform float phase_shift;
uniform int num_sources;

void main()
{
    const float pi = 3.14159265358979323846;

    float array_width = (float(num_sources) - 1.0) / (4.75 * float(num_sources) + 10.0);
    float source_spacing = array_width / float(num_sources - 1);
    float wavelength = (num_sources == 1) ? 0.21 : 4.0 * source_spacing;
    float k = 2.0 * pi / wavelength;
    const float amplitude = 0.2;

    vec2 xy = gl_FragCoord.xy / screen_height;

    float wave = 0.0;
    for (int i = 0; i < num_sources; ++i)
    {
        float source_y = 0.5 - array_width * 0.5 + float(i) * source_spacing;
        float r = distance(vec2(0.1, source_y), xy);
        float phase = (float(i) - float(num_sources - 1) * 0.5) * phase_shift * pi / 180.0;
        wave += amplitude / r * cos(-k * r + phase);
    }

    // NOTE: `wave` is the physical wave function
    // The values below are just arbitrarily processed to look nice
    float wave_pos = sqrt(clamp(wave / float(num_sources), 0.0, 1.0));
    float wave_neg = sqrt(clamp(-wave / float(num_sources), 0.0, 1.0));
    color = vec4(wave_pos, 0.6 * wave_pos + 0.4 * wave_neg, wave_neg, 1.0);
}
