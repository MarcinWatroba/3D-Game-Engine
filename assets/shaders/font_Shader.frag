#version 330

in vec2 TexCoord;

out vec4 colour;

uniform sampler2D object_Texture;

void main()
{
	colour = texture(object_Texture, vec2(TexCoord.x, TexCoord.y));
}