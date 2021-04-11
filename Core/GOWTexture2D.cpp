#include "GOWTexture.h"

using namespace GOW;

GOWTexture2D::GOWTexture2D()
:GOWTexture()
{
	Target = GL_TEXTURE_2D;
}

GOWTexture2D::GOWTexture2D(uint32 InResX, 
						uint32 InResY,
						GLenum InIternalFormat, 
						GLenum InType, 
						GLenum InFormat)
:GOWTexture()
{
	Target = GL_TEXTURE_2D;
	CreateEmpty(InResX, 
				InResY,
				InIternalFormat,
				InType,
				InFormat);
}

GOWTexture2D::GOWTexture2D(const GOW::GOWImage& InImage)
:GOWTexture()
{
	Target = GL_TEXTURE_2D;
	Load(InImage);
}

GOWTexture2D::GOWTexture2D(const std::string& InPath)
:GOWTexture()
{
	Target = GL_TEXTURE_2D;
	Load(InPath);
}

GOWTexture2D::~GOWTexture2D()
{

}

void GOWTexture2D::CreateEmpty(uint32 InResX,
							uint32 InResY, 
							GLenum InInteranlFormat,
							GLenum InType, 
							GLenum InFormat)
{
	Width = InResX;
	Height = InResY;

	Bind();
	glTexImage2D(GL_TEXTURE_2D,
				0, 
				InInteranlFormat, 
				InResX, 
				InResY, 
				0, 
				InFormat, 
				InType, 
				nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	UnBind();
}

bool GOWTexture2D::Load(const std::string& InPath)
{
	GOWImage Image;
	if (!Image.Load(InPath))
		return false;

	Width = Image.Width;
	Height = Image.Height;

	return Load(Image);
}

bool GOWTexture2D::Load(const GOW::GOWImage& InImage)
{
	if (!InImage.Image)
		return false;

	SDL_Surface* SurfaceImage = SDL_ConvertSurfaceFormat(InImage.Image,
														SDL_PIXELFORMAT_RGBA8888, 
														0);

	if (!SurfaceImage)
		return false;

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 
				0, 
				GL_RGBA,
				Width,
				Height,
				0,
				GL_RGBA, 
				GL_UNSIGNED_INT_8_8_8_8, 
				SurfaceImage->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	UnBind();

	SDL_FreeSurface(SurfaceImage);

	return true;
}

void GOWTexture2D::Bind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_2D, Texture);
}

void GOWTexture2D::UnBind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}