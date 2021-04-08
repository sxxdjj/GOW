#include "GOWTexture.h"

using namespace GOW;

GOWTexture1DArray::GOWTexture1DArray()
:GOWTexture()
{
	Target = GL_TEXTURE_1D_ARRAY;
}

GOWTexture1DArray::GOWTexture1DArray(uint32 InRes,
									uint32 InNumLayers,
									GLenum InInternalFormat,
									GLenum InType,
									GLenum InFormat)
:GOWTexture()
{
	Target = GL_TEXTURE_1D_ARRAY;
	CreateEmpty(InRes, InNumLayers, InInternalFormat, InType, InFormat);
}

GOWTexture1DArray::GOWTexture1DArray(const std::vector<GOW::GOWImage>& InImages)
:GOWTexture()
{
	Target = GL_TEXTURE_1D_ARRAY;
	Load(InImages);
}

GOWTexture1DArray::GOWTexture1DArray(const std::vector<std::string>& InPaths)
:GOWTexture()
{
	Target = GL_TEXTURE_1D_ARRAY;
	Load(InPaths);
}

GOWTexture1DArray::~GOWTexture1DArray()
{

}

void GOWTexture1DArray::CreateEmpty(uint32 InRes,
									uint32 InNumLayers,
									GLenum InInternalFormat,
									GLenum InType,
									GLenum InFormat)
{
	Width = InRes;
	Height = 1;
	NumLayers = InNumLayers;

	Bind();
	glTexImage2D(GL_TEXTURE_1D_ARRAY, 
				0,
				InInternalFormat, 
				InRes, 
				InNumLayers,
				0, 
				InFormat, 
				InType, 
				nullptr);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	UnBind();
}

bool GOWTexture1DArray::Load(const std::vector<std::string>& InPaths)
{
	if (InPaths.size() <= 0)
		return false;

	std::vector<GOWImage> Images(InPaths.size());

	for (uint32 i = 0; i < InPaths.size(); i++)
	{
		if (!Images[i].Load(InPaths[i]))
			return false;
	}

	return Load(Images);
}

bool GOWTexture1DArray::Load(const std::vector<GOW::GOWImage>& InImages)
{
	Width = 0;
	Height = 1;
	NumLayers = InImages.size();

	std::vector<SDL_Surface*> SurfaceImages(InImages.size());

	for (uint32 i = 0; i < InImages.size(); i++)
	{
		if (!InImages[i].Image)
			return false;

		if (Width == 0)
		{
			Width = InImages[i].Width;

			if (Width == 0)
				return false;
		}
		else if (Width != InImages[i].Width)
		{
			return false;
		}

		SurfaceImages[i] = SDL_ConvertSurfaceFormat(InImages[i].Image, 
													SDL_PIXELFORMAT_ABGR8888, 
													0);

		if (!SurfaceImages[i])
			return false;
	}

	Bind();
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_1D_ARRAY, 
				0, 
				GL_RGBA, 
				Width, 
				NumLayers,
				0, 
				GL_RGBA, 
				GL_UNSIGNED_INT_8_8_8_8, 
				nullptr);
	for (uint32 i = 0; i < NumLayers; i++)
	{
		glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 
						0, 
						0,
						i,
						Width,
						1,
						GL_RGBA,
						GL_UNSIGNED_INT_8_8_8_8, 
						SurfaceImages[i]->pixels);
	}
	glGenerateMipmap(GL_TEXTURE_1D_ARRAY);
	UnBind();

	return true;
}

void GOWTexture1DArray::Bind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_1D_ARRAY, Texture);
}

void GOWTexture1DArray::UnBind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
}