#version 330

layout(location = 0) out vec4 color;

in vec2 texture_coords;
in vec4	active_color_geom;

//uniform float start;
//uniform float end;
uniform sampler2D edge_tex;

void	main()
{
	vec4 temp_color;

	temp_color = texture(edge_tex, texture_coords);
	color = vec4(temp_color.g, temp_color.b, temp_color.r, temp_color.a);
	color *= vec4(mix(vec3(1), active_color_geom.xyz, float(active_color_geom.a > 0.99)), 1);
	if (color.a < 0.9)
		discard;
}
