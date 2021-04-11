#include "GOWTexture.h"

using namespace GOW;

GOWTexture3D::GOWTexture3D()
:GOWTexture()
{
	Target = GL_TEXTURE_3D;
}

GOWTexture3D::GOWTexture3D(uint32 InResX, 
						uint32 InResY, 
						uint32 InResZ, 
						GLenum InInternalFormat, 
						GLenum InType,
						GLenum InFormat)
:GOWTexture()
{
	Target = GL_TEXTURE_3D;
	CreatEmpty(InResX, 
			InResY, 
			InResZ, 
			InInternalFormat, 
			InType, 
			InFormat);
}

GOWTexture3D::GOWTexture3D(const std::vector<GOW::GOWImage>& InImages)
{
	Target = GL_TEXTURE_3D;
	Load(InImages);
}

GOWTexture3D::GOWTexture3D(const std::vector<std::string>& InPaths)
{
	Target = GL_TEXTURE_3D;
	Load(InPaths);
}

GOWTexture3D::~GOWTexture3D()
{

}

void GOWTexture3D::CreatEmpty(uint32 InResX,
							uint32 InResY,
							uint32 InResZ,
							GLenum InInternalFormat,
							GLenum InType,
							GLenum InFormat)
{
	Width = InResX;
	Height = InResY;
	NumLayers = InResZ;

	Bind();
	glTexImage3D(GL_TEXTURE_3D, 
				0, 
				InInternalFormat, 
				InResX, 
				InResY, 
				InResZ, 
				0, 
				InFormat, 
				InType,
				nullptr);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	UnBind();
}

bool GOWTexture3D::Load(const std::vector<std::string>& InPaths)
{
	std::vector<GOWImage> Images(InPaths.size());

	for (uint32 i = 0; i < InPaths.size(); i++)
	{
		if (!Images[i].Load(InPaths[i]))
			return false;
	}

	return Load(Images);
}

bool GOWTexture3D::Load(const std::vector<GOW::GOWImage>& InImages)
{
	Width = 0;
	Height = 0;
	NumLayers = InImages.size();

	std::vector<SDL_Surface*> SurfaceImages(NumLayers);

	for (uint32 i = 0; i < NumLayers; i++)
	{
		if (!InImages[i].Image)
			return false;

		if (Width == 0 && Height == 0)
		{
			Width = InImages[i].Width;
			Height = InImages[i].Height;

			if (Width == 0 || Height == 0)
				return false;

			SurfaceImages[i] = SDL_ConvertSurfaceFormat(InImages[i].Image, 
														SDL_PIXELFORMAT_RGBA8888, 
														0);
			if (!SurfaceImages[i])
				return false;
		}
	}

	Bind();
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage3D(GL_TEXTURE_3D, 
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
		glTexSubImage3D(GL_TEXTURE_3D,
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
	glGenerateMipmap(GL_TEXTURE_3D);
	UnBind();

	for (SDL_Surface* SurfaceImage : SurfaceImages)
	{
		SDL_FreeSurface(SurfaceImage);
	}

	return true;
}

void GOWTexture3D::Bind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_3D, Texture);
}

void GOWTexture3D::UnBind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, 0);
}