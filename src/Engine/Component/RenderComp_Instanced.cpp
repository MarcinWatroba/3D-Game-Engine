#include <Engine\Component\RenderComp_Instanced.h>
#include <Engine\Mesh\Mesh_Instanced.h>
#include <Engine\Creators\Shader.h>
#include <glad\glad.h>

RenderComp_Instanced::RenderComp_Instanced(const RenderComp_Instanced &p_NewComp_In) : RenderComp(p_NewComp_In)
{}
std::string RenderComp_Instanced::get_Type()
{
	return "RenderComp_Instanced";
}

void RenderComp_Instanced::renderInstanced(int draw_Mode_In, int draw_Shape_In, Shader* p_Shader_In, int max, int count, float positions[])
{

}

void RenderComp_Instanced::renderInstanceed(int draw_Mode_In, int draw_Shape_In, Shader * p_Shader_In, int max, int count, float positions[], int VAO_In, int buff_In, int size_In)
{
	//Bind lightning maps
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, get_Texture("Diffuse_Map"));

	//GLint diffuseLoc = glGetUniformLocation(p_Shader_In->get_Program(), "diffuse");
	//glUniform1i(diffuseLoc, 0);


	glBindBuffer(GL_ARRAY_BUFFER, buff_In);
	glBufferData(GL_ARRAY_BUFFER, max * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, to improve streaming perf.
	glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(GLfloat) * 3, positions);


	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);
	glVertexAttribDivisor(2, 1);

	////Draw
	glBindVertexArray(VAO_In);
	glDrawElementsInstanced(GL_TRIANGLES, size_In, GL_UNSIGNED_INT, 0, count);   	//draw elements as triangles 
																			//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, count);   	//draw elements as triangles 
																			//Pass texture to the shader


	glBindVertexArray(0);
}

void RenderComp_Instanced::render(int i_DrawMode_In, int i_DrawShape_In, Shader * p_Shader_In)
{
	//glBindBuffer(GL_ARRAY_BUFFER, p_Mesh->get_InstanceBufferHandle());
}

void RenderComp_Instanced::render(int i_DrawMode_In, int i_DrawShape_In, Shader * p_Shader_In, int max, int count, float positions[])
{
}
