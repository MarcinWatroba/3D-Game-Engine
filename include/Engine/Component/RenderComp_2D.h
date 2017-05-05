#pragma once

#include <Engine\Component\RenderComp.h>

class RenderComp_2D : public RenderComp
{
public:
	//Render
	RenderComp_2D();
	RenderComp_2D(const RenderComp_2D &p_NewComp_In);
	~RenderComp_2D() {};
	void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In);
	void renderInstanced(int draw_Mode_In, int draw_Shape_In, Shader * p_Shader_In, int max, int count, float positions[], int VAO_In, int buff_In, int size_In);
	std::string get_Type();
};