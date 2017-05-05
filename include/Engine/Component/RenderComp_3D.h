#pragma once

#include <Engine\Component\RenderComp.h>
class Mesh_3D;

class RenderComp_3D : public RenderComp
{
private:
	float f_Shininess; // Shininess
public:
	//Render
	RenderComp_3D() {};
	RenderComp_3D(const RenderComp_3D &p_NewComp_In);
	~RenderComp_3D() {};
	void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In);
	void set_Shininess(float f_Shininess_In);
	float get_Shininess();
	std::string get_Type();
};