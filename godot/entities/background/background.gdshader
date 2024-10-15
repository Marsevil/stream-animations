shader_type canvas_item;

uniform sampler2D offsets: repeat_enable;

void fragment() {
	float tex_val = texture(TEXTURE, UV).r;
	float delay = TAU * texture(offsets, UV).r;

	float amp_val = (sin(TIME + delay) + 1.0) / 2.0;

	float out_val = tex_val * amp_val;

	COLOR = vec4(out_val, out_val, out_val, 1.0);
}
