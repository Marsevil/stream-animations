shader_type canvas_item;

uniform vec4 color: source_color = vec4(1.0, 1.0, 1.0, 1.0);
uniform float percent_show: hint_range(0.0, 1.0, 0.01) = 1.0;
uniform uint nb_lines = 5;
uniform float stroke_ratio = .015;

vec2 grid(vec2 uv, uint cols, uint rows) {
	return fract(vec2(uv.x * float(cols), uv.y * float(rows)));
}

void fragment() {
	vec2 grid_uv = grid(UV, nb_lines, nb_lines);
	float half_stroke = stroke_ratio / 2.0;
	bool in_col;
	{
		bool x_in_bound = grid_uv.x > 0.5 - half_stroke && grid_uv.x < 0.5 + half_stroke;
		bool y_in_bound = 1.0 - UV.y < percent_show;
		in_col = x_in_bound && y_in_bound;
	}
	bool in_row;
	{
		bool y_in_bound = grid_uv.y > 0.5 - half_stroke && grid_uv.y < 0.5 + half_stroke;
		bool x_in_bound = UV.x < percent_show;
		in_row = x_in_bound && y_in_bound;
	}
	if (!in_col && !in_row) {
		discard;
	}
	COLOR = color;
}
