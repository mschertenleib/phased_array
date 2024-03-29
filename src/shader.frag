#version 330

out vec4 color;

uniform int screen_height;
uniform int num_sources;
uniform float source_spacing;
uniform float wavelength;
uniform float phase_shift;

void main()
{
    float array_width = float(num_sources - 1) * source_spacing;
    const float pi = 3.14159265358979323846;
    float k = 2.0 * pi / wavelength;
    const float amplitude = 0.2;

    vec2 xy = gl_FragCoord.xy / screen_height;

    float wave = 0.0;
    for (int i = 0; i < num_sources; ++i)
    {
        float source_y = 0.5 - array_width * 0.5 + float(i) * source_spacing;
        float r = distance(vec2(0.08, source_y), xy);
        float phase = (float(i) - float(num_sources - 1) * 0.5) * phase_shift * pi / 180.0;
        wave += amplitude / r * cos(-k * r + phase);
    }

    // NOTE: `wave` is the physical wave function.
    // The values here are just arbitrarily processed to look nice,
    // and make the wave visible despite the 1/r fading.
    float wave_pos = sqrt(clamp(wave / float(num_sources), 0.0, 1.0));
    float wave_neg = sqrt(clamp(-wave / float(num_sources), 0.0, 1.0));
    color = vec4(wave_pos, 0.6 * wave_pos + 0.4 * wave_neg, wave_neg, 1.0);
}
