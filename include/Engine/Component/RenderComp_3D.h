#pragma once

#include <Engine\Component\RenderComp.h>
class Mesh_3D;

class RenderComp_3D : public RenderComp
{
private:
	float f_Shininess; // Shininess
public:

	//Render
	void renderDepth(int draw_Mode_In, int draw_Shape_In, Shader * p_Shader_In);
	void renderInstanced(int draw_Mode_In, int draw_Shape_In, Shader * p_Shader_In, int max, int count, float positions[]);
	void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In);
	void set_Shininess(float f_Shininess_In);
	float get_Shininess();
};