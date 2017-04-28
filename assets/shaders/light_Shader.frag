#version 330

out vec4 colour;
uniform vec3 light_Colour;

void main()
{
	colour = vec4(light_Colour, 1.f);
}