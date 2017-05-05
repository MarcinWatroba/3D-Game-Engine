#include <Engine\Component\RenderComp_2D.h>
#include <Engine\Mesh\Mesh_2D.h>
#include <glad\glad.h>
#include <Engine\Creators\Texture.h>
#include <Engine\Creators\Shader.h>

RenderComp_2D::RenderComp_2D()
{
	v3_Colour = glm::vec3(1.f, 1.f, 1.f);
}

RenderComp_2D::RenderComp_2D(const RenderComp_2D & p_NewComp_In) : RenderComp(p_NewComp_In)
{

}

void RenderComp_2D::render(int i_DrawMode_In, int i_DrawShape_In, Shader * p_Shader_In)
{
	//Bind lightning maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, get_Texture("Texture_Atlas")->get_Texture());

	GLint textureLoc = glGetUniformLocation(p_Shader_In->get_Program(), "object_Texture");
	glUniform1i(textureLoc, 0);

	//Tiles
	GLint tileLoc = glGetUniformLocation(p_Shader_In->get_Program(), "tiling");
	glUniform2f(tileLoc, get_Tiles().x, get_Tiles().y);

	GLint colourLoc = glGetUniformLocation(p_Shader_In->get_Program(), "rgb_Colour");
	glUniform3f(colourLoc, get_Colour().x, get_Colour().y, get_Colour().z);

	//Draw
	glBindVertexArray(p_Mesh->get_VAO());
	glDrawElements(GL_TRIANGLES, p_Mesh->get_SizeOfIndices(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::string RenderComp_2D::get_Type()
{
	return "RenderComp_2D";
}
