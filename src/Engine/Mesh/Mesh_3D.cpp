#include <Engine\Mesh\Mesh_3D.h>
#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <iostream>

Mesh_3D::Mesh_3D(const char* pc_FileName_In, int i_DrawMode_In)
{
	std::ifstream file;
	std::istringstream stream;
	std::string line;
	char token;
	file.open(pc_FileName_In);

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			stream.str(line);
			stream >> token;

			switch (token)
			{
			case 'v':

				Vertex f_Vertex;
				stream >> f_Vertex.x;
				stream >> f_Vertex.y;
				stream >> f_Vertex.z;
				vf_Vertices.push_back(f_Vertex);
				break;

			case 'n':
				Normal f_Normal;
				stream >> f_Normal.x;
				stream >> f_Normal.y;
				stream >> f_Normal.z;
				vf_Normals.push_back(f_Normal);
				break;

			case 't':
				UV f_UV;
				stream >> f_UV.u;
				stream >> f_UV.v;
				vf_UVs.push_back(f_UV);

				break;

			case 'f':
				for (int i = 0; i < 3; i++)
				{
					Face ui_Face;
					stream >> ui_Face.vertex;
					stream.get();
					stream >> ui_Face.uv;
					stream.get();
					stream >> ui_Face.normal;
					vui_Faces.push_back(ui_Face);
				}
				break;
			}
			stream.clear();
		}
		file.close();
	}
	else
	{
		std::cout << "Failed to open the file at: " << pc_FileName_In << "\n";
	}

	unsigned int i_Counter = 0;

	for (unsigned int i = 0; i < vui_Faces.size(); i++)
	{
		VertexIndex random = VertexIndex(vui_Faces.at(i).vertex - 1, vui_Faces.at(i).uv - 1, vui_Faces.at(i).normal - 1);

		auto found = moui_Indices.find(random);

		if (found == moui_Indices.end())
		{
			moui_Indices.insert(std::pair<VertexIndex, unsigned int>(random, i_Counter));

			CompleteVertex comp_Vertex;
			comp_Vertex.vertex = vf_Vertices.at(vui_Faces.at(i).vertex - 1);
			comp_Vertex.uv = vf_UVs.at(vui_Faces.at(i).uv - 1);
			comp_Vertex.normal = vf_Normals.at(vui_Faces.at(i).normal - 1);

			vf_Data.push_back(comp_Vertex);
			vui_Indices.push_back(i_Counter);
			i_Counter++;
		}
		else
		{
			vui_Indices.push_back(found->second);
		}		
	}


	//It's time to create buffers here
 	glGenVertexArrays(1, &ui_VAO);
	glGenBuffers(1, &ui_EBO);
	glGenBuffers(1, ui_VBO);

	glBindVertexArray(ui_VAO);

	//Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, ui_VBO[Buffer::Vertex]);
	glBufferData(GL_ARRAY_BUFFER, vf_Data.size() * sizeof(CompleteVertex), vf_Data.data(), i_DrawMode_In);

	//Bind object buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ui_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vui_Indices.size() * sizeof(GLuint), vui_Indices.data(), i_DrawMode_In);

	//Vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CompleteVertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//UV attributes
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CompleteVertex), (GLvoid*)(sizeof(Vertex)));
	glEnableVertexAttribArray(1);

	//Normal attributes
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CompleteVertex), (GLvoid*)(sizeof(Vertex) + sizeof(UV)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

//unsigned int Mesh_3D::get_InstanceBufferHandle()
//{
//	return 0;
//}
