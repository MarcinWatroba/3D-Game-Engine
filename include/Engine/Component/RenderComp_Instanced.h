#pragma once

#include <Engine\Component\RenderComp.h>
class Mesh_Instanced;

class RenderComp_Instanced : public RenderComp
{
private:

public:

	void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In);
	void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In, int max, int count, float positions[]);
	void renderInstanced(int draw_Mode_In, int draw_Shape_In, Shader* p_Shader_In, int max, int count, float positions[]);
	void renderInstanceed(int draw_Mode_In, int draw_Shape_In, Shader * p_Shader_In, int max, int count, float positions[], int VAO_In, int buff_In, int size_In);

};