shader_type canvas_item;

uniform sampler2D offsets: repeat_enable;
uniform uvec2 amp_size = uvec2(512, 512);
uniform float min_value = 0.5;
uniform float time = 0.0;

void fragment() {
	float tex_val = texture(TEXTURE, UV).r;
	float delay = 2.0 * PI * texture(offsets, UV).r;

	float amp_val = (sin(time + delay) + 1.0) / 2.0;

	float out_val = tex_val * amp_val;

	COLOR = vec4(out_val, out_val, out_val, 1.0);
}
