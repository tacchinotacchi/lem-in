in vec3 world_coord;

uniform uint start;
uniform uint end;
uniform mat4 view
uniform mat4 proj

void	main()
{
	gl_Position = proj * view * vec4(world, 1.0);
	start = (start == id);
	end = (end == id);
}
