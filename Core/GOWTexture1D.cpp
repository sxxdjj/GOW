#include "GOWTexture.h"

using namespace GOW;

GOWTexture1D::GOWTexture1D()
:GOWTexture()
{
	Target = GL_TEXTURE_1D;
}

GOWTexture1D::GOWTexture1D(uint32 InRes, GLenum InInternalFormat, GLenum InType, GLenum InFormat)
:GOWTexture()
{
	Target = GL_TEXTURE_1D;
	CreateEmpty(InRes, InInternalFormat, InType, InFormat);
}

GOWTexture1D::GOWTexture1D(const GOW::GOWImage& InImage)
:GOWTexture()
{
	Target = GL_TEXTURE_1D;
	Load(InImage);
}

GOWTexture1D::GOWTexture1D(const std::string& InPath)
:GOWTexture1D()
{
	Target = GL_TEXTURE_1D;
	Load(InPath);
}

GOWTexture1D::~GOWTexture1D()
{

}

void GOWTexture1D::CreateEmpty(uint32 InRes, GLenum InInternalFormat, GLenum InType, GLenum InFormat)
{
	Width = InRes;
	Height = 1;

	Bind();
	glTexImage1D(GL_TEXTURE_1D, 0, InInternalFormat, InRes, 0, InFormat, InType, nullptr);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	UnBind();
}

bool GOWTexture1D::Load(const std::string& InPath)
{
	GOWImage Image;
	if (!Image.Load(InPath))
	{
		return false;
	}

	Width = Image.Width;

	return Load(Image);
}

bool GOWTexture1D::Load(const GOWImage& InImage)
{
	if (!InImage.Image)
		return false;

	SDL_Surface* Tmp = SDL_ConvertSurfaceFormat(InImage.Image, SDL_PIXELFORMAT_RGBA8888, 0);

	if (!Tmp)
		return false;

	Bind();

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, InImage.Width, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, Tmp->pixels);
	glGenerateMipmap(GL_TEXTURE_1D);

	UnBind();
	
	SDL_FreeSurface(Tmp);

	return true;
}

void GOWTexture1D::Bind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_1D, Texture);
}

void GOWTexture1D::UnBind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_1D, 0);
}