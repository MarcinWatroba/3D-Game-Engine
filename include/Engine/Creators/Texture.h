#pragma once

class Texture
{
private:
	unsigned int ui_Texture; // Texture

	//Size
	int i_Width;
	int i_Height; 
	unsigned char* puc_Image; // Our texture

public:
	//Constructor
	Texture() {}

	//Main constructor
	Texture(const char* pc_TextureName_In, int i_TextureMode_In, int i_WrappingS_In, 
		int i_WrappingT_In, int i_FilterMin_In, int i_FilterMag_In, int i_ColourChannel_In, int i_ColourFormat_In, bool b_GenMipmap_In);

	//Get loaded texture
	unsigned int get_Texture();
};
