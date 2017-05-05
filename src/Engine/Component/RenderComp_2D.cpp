//#include <RenderComp_2D.h>

//void RenderComp_2D::render(int i_DrawMode_In, int i_DrawShape_In)
//{
//	//Bind the texture
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(i_DrawMode_In, mso_Textures.find("Default")->second->get_Texture());
//
//	//Implement use shader here
//	glUseProgram(po_Shader->get_Program());
//
//	//Pass texture to the shader
//	glUniform1i(glGetUniformLocation(po_Shader->get_Program(), "object_Texture"), 0);
//
//	//Uniform locations
//	GLint modelLoc = glGetUniformLocation(po_Shader->get_Program(), "model");
//	GLint projLoc = glGetUniformLocation(po_Shader->get_Program(), "projection");
//
//	//Pass them to shaders
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(*pmat4_Model));
//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(*pmat4_Projection));
//
//	//Draw elements
//	glBindVertexArray(ui_Vao);
//	glDrawElements(i_DrawShape_In, vui_Indices.size(), GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}