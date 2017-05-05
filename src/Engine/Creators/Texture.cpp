#include <Engine\Creators\Texture.h>
#include <glad\glad.h>
#include <SOIL\SOIL.h>

Texture::Texture(const char* pc_TextureName_In, int i_TextureMode_In, int i_WrappingS_In,
	int i_WrappingT_In, int i_FilterMin_In, int i_FilterMag_In, int i_ColourChannel_In, int i_ColourFormat_In, bool b_GenMipmap_In, std::string s_ID_In)
{
	s_ID = s_ID_In;

	//Generate texture
	glGenTextures(1, &ui_Texture);
	glBindTexture(i_TextureMode_In, ui_Texture); // Bind it

										  //Texture wrapping
	glTexParameteri(i_TextureMode_In, GL_TEXTURE_WRAP_S, i_WrappingS_In);
	glTexParameteri(i_TextureMode_In, GL_TEXTURE_WRAP_T, i_WrappingT_In);

	//Texture filtering
	glTexParameteri(i_TextureMode_In, GL_TEXTURE_MIN_FILTER, i_FilterMin_In);
	glTexParameteri(i_TextureMode_In, GL_TEXTURE_MAG_FILTER, i_FilterMag_In);

	int i_Width;
	int i_Height;

	//Load the image
	puc_Image = SOIL_load_image(pc_TextureName_In, &i_Width, &i_Height, 0, i_ColourChannel_In);

	v2_Size = glm::vec2(i_Width, i_Height);

	//Decide what kind of texture it is
	switch (i_TextureMode_In)
	{
		//1D texture is not supported
	case GL_TEXTURE_1D:
		throw;
		break;

		//2D texture is supported
	case GL_TEXTURE_2D:



		glTexImage2D(i_TextureMode_In, 0, i_ColourFormat_In, i_Width, i_Height, 0, i_ColourFormat_In, GL_UNSIGNED_BYTE, puc_Image);
		break;

		//3D texture is not supported
	case GL_TEXTURE_3D:
		throw;
		break;
	}

	//Generate mipmap
	if (b_GenMipmap_In) glGenerateMipmap(i_TextureMode_In);

	//Free image
	SOIL_free_image_data(puc_Image);

	glBindTexture(i_TextureMode_In, 0);


}

unsigned int Texture::get_Texture()
{
	return ui_Texture;
}

std::string Texture::get_ID()
{
	return s_ID;
}

glm::vec2 Texture::get_Size()
{
	return v2_Size;
}