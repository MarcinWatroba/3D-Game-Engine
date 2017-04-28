#pragma once

#include <Engine/Mesh/Mesh.h>

namespace Buffer
{
	enum Buffer{ Vertex, Normal, UV, Num};
}

class Mesh_3D : public Mesh
{
private:
	unsigned int ui_VBO[Buffer::Num];
public:
	Mesh_3D() {};
	Mesh_3D(const char* pc_FileName_In, int i_DrawMode_In);
};