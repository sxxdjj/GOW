#include "GOWTexture.h"

using namespace GOW;

GOWCubMap::GOWCubMap()
:GOWTexture()
{
	Target = GL_TEXTURE_CUBE_MAP;
}

GOWCubMap::GOWCubMap(uint32 InResX,
					uint32 InResY, 
					GLenum InInternalFormat, 
					GLenum InType, 
					GLenum InFormat)
:GOWTexture()
{
	Target = GL_TEXTURE_CUBE_MAP;
	CreateEmpty(InResX, InResY, InInternalFormat, InType, InFormat);
}

GOWCubMap::GOWCubMap(const GOW::GOWImage& InPosX, 
					const GOW::GOWImage& InNegX, 
					const GOW::GOWImage& InPosY,
					const GOW::GOWImage& InNegY, 
					const GOW::GOWImage& InPosZ, 
					const GOW::GOWImage& InNegZ)
:GOWTexture()
{
	Target = GL_TEXTURE_CUBE_MAP;
	Load(InPosX, InNegX, InPosY, InNegY, InPosZ, InNegZ);
}

GOWCubMap::~GOWCubMap()
{

}

void GOWCubMap::CreateEmpty(uint32 InResX, 
							uint32 InResY, 
							GLenum InInternalFormat,
							GLenum InType, 
							GLenum InFormat)
{
	Width = InResX;
	Height = InResY;
	
	Bind();
	for (uint32 i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, 
					InInternalFormat, 
					InResX, 
					InResY, 
					0, 
					InFormat, 
					InType,
					nullptr);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	UnBind();
}

bool GOWCubMap::Load(const std::string& InPosX, 
					const std::string& InNegX, 
					const std::string& InPosY, 
					const std::string& InNegY, 
					const std::string& InPosZ, 
					const std::string& InNegZ)
{
	GOWImage PositiveX(InPosX);
	GOWImage NegativeX(InNegX);
	GOWImage PositiveY(InPosY);
	GOWImage NegativeY(InNegY);
	GOWImage PositiveZ(InPosZ);
	GOWImage NegativeZ(InNegZ);

	return Load(PositiveX, NegativeX, PositiveY, NegativeY, PositiveZ, NegativeZ);
}

bool GOWCubMap::Load(const GOWImage& InPosX,
					const GOWImage& InNegX,
					const GOWImage& InPosY,
					const GOWImage& InNegY, 
					const GOWImage& InPosZ, 
					const GOWImage& InNegZ)
{
	SDL_Surface* SurfaceImage;
	std::vector<const GOWImage*> Faces = { &InPosX, 
										&InNegX, 
										&InPosY, 
										&InNegY,
										&InPosZ,
										&InNegZ };
	Bind();
	for (uint32 i = 0; i < 6; i++)
	{
		SurfaceImage = SDL_ConvertSurfaceFormat(Faces[i]->Image, SDL_PIXELFORMAT_ABGR8888, 0);

		if (!SurfaceImage)
			return false;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
					0,
					GL_RGBA, 
					Faces[i]->Width,
					Faces[i]->Height, 
					0, 
					GL_RGBA,
					GL_UNSIGNED_INT_8_8_8_8,
					SurfaceImage->pixels);

		SDL_FreeSurface(SurfaceImage);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	UnBind();

	return true;
}

void GOWCubMap::Bind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + InTextureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Texture);
}

void GOWCubMap::UnBind(uint32 InTextureUnit /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}