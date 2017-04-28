#pragma once

#include <Engine\Component\RenderComp.h>

class RenderComp_2D : public RenderComp
{
public:
	//Render
	void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In);
};