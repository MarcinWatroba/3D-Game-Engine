#include <Engine/Mesh/Mesh.h>

unsigned int Mesh::get_VAO()
{
	return ui_VAO;
}

unsigned int Mesh::get_SizeOfIndices()
{
	return vui_Indices.size();
}

