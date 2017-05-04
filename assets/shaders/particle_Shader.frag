#version 430

in vec2 TexCoord;

uniform sampler2D diffuse;

layout (location=0) out vec4 FragColour;

void main() {
    FragColour = vec4(1.0);
	//FragColour = texture(diffuse, vec2(TexCoord.x * tiling.x, (1 - TexCoord.y) * tiling.y));
}
