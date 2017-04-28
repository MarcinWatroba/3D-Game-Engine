#pragma once

#include <Engine\Component\RenderComp.h>
class Mesh_3D;

class RenderComp_3D : public RenderComp
{
private:
	float f_Shininess; // Shininess
public:
	//Render
	void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In);
	void set_Shininess(float f_Shininess_In);
	float get_Shininess();
};