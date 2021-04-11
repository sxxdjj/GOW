#include "GOWTexture.h"

using namespace GOW;

GOWTexture2DArray::GOWTexture2DArray()
:GOWTexture()
{
	Target = GL_TEXTURE_2D_ARRAY;
}

GOWTexture2DArray::GOWTexture2DArray(uint32 InResX, 
									uint32 InResY, 
									uint32 InNumLayers, 
									GLenum InInternalFormat, 
									GLenum InType, 
									GLenum InFormat)
:GOWTexture()
{
	Target = GL_TEXTURE_2D_ARRAY;
	CreateEmpty(InResX,
				InResY, 
				InNumLayers,
				InInternalFormat,
				InType, 
				InFormat);
}

GOWTexture2DArray::GOWTexture2DArray(const std::vector<GOW::GOWImage>& InImages)
:GOWTexture()
{
	Target = GL_TEXTURE_2D_ARRAY;
	Load(InImages);
}

GOWTexture2DArray::GOWTexture2DArray(const std::vector<std::string>& InPaths)
:GOWTexture()
{
	Target = GL_TEXTURE_2D_ARRAY;
	Load(InPaths);
}

GOWTexture2DArray::~GOWTexture2DArray()
{

}

void GOWTexture2DArray::CreateEmpty(uint32 InResX,
									uint32 InResY,
									uint32 InNumLayers,
									GLenum InInternalFormat,
									GLenum InType,
									GLenum InFormat)
{
	Width = InResX;
	Height = InResY;

	NumLayers = InNumLayers;

	Bind();
	
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 
				0, 
				InInternalFormat, 
				InResX, 
				InResY,
				InNumLayers,
				0, 
				InFormat, 
				InType, 
				nullptr);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	UnBind();
}
bool GOWTexture2DArray::Load(const std::vector<std::string>& InPaths)
{
	std::vector<GOWImage> Images(InPaths.size());

	for (uint32 i = 0; i < InPaths.size(); i++)
	{
		if (!Images[i].Load(InPaths[i]))
			return false;
	}

	return Load(Images);
}

bool GOWTexture2DArray::Load(const std::vector<GOW::GOWImage>& InImages)
{
	Width = 0;
	Height = 0;
	NumLayers = InImages.size();

	std::vector<SDL_Surface*> SurfaceImages(InImages.size());

	for (uint32 i = 0; i < NumLayers; i++)
	{
		if (!InImages[i].Image)
			return false;

		if (Width == 0 && Height == 0)
		{
			Width = InImages[i].Width;
			Height = InImages[i].Height;

			if (Width == 0 || Height == 0)
			{
				return false;
			}
		}
		else if (Width != InImages[i].Width || Height != InImages[i].Height)
		{
			return false;
		}

		SurfaceImages[i] = SDL_ConvertSurfaceFormat(InImages[i].Image, SDL_PIXELFORMAT_RGBA8888, 0);

		if (!SurfaceImages[i])
			return false;
	}

	Bind();

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage3D(GL_TEXTURE_2D_ARRAY,
				0,
				GL_RGBA,
				Width, 
				Height,
				NumLayers,
				0, 
				GL_RGBA, 
				GL_UNSIGNED_INT_8_8_8_8, 
				nullptr);

	for (uint32 i = 0; i < NumLayers; i++)
	{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
						0, 
						0,
						0, 
						i, 
						Width, 
						Height, 
						1, 
						GL_RGBA,
						GL_UNSIGNED_INT_8_8_8_8, 
						SurfaceImages[i]->pixels);
	}
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	UnBind();

	for (SDL_Surface* SurfaceImage : SurfaceImages)
	{
		SDL_FreeSurface(SurfaceImage);
	}

	return true;
}

void GOWTexture2DArray::Bind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_2D_ARRAY, Texture);
}

void GOWTexture2DArray::UnBind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}