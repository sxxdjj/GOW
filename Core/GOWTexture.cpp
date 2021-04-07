#include "GOWTexture.h"

using namespace GOW;

std::map<std::string, std::shared_ptr<GOWTexture>> GOWTexture::Textures;

GOWTexture::GOWTexture()
{
	Width = 0;
	Height = 0;
	NumLayers = 1;
	glGenTextures(1, &Texture);
}

GOWTexture::~GOWTexture()
{
	glDeleteTextures(1, &Texture);
}

void GOWTexture::SetParameter(GLenum InName, int InParameter)
{
	Bind();
	glTexParameteri(Target, InName, InParameter);
	UnBind();
}

void GOWTexture::SetParameter(GLenum InName, float InParameter)
{
	Bind();
	glTexParameterf(Target, InName, InParameter);
	UnBind();
}

bool GOWTexture::StoreTexture(std::string InName, std::shared_ptr<GOWTexture> InTexture)
{
	return Textures.insert(std::make_pair(InName, InTexture)).second;
}

std::shared_ptr<GOWTexture> GOWTexture::FindTexture(std::string InName)
{
	const auto& It = Textures.find(InName);
	if (It == Textures.end())
		return nullptr;

	return It->second;
}

void GOWTexture::AddPath(std::string InPath)
{
	GOWImage::AddPath(InPath);
}

void GOWTexture::BindImage(GLuint InUnit,
						GLint InLevel,
						GLboolean InLayered,
						GLint InLayer,
						GLenum InAccess,
						GLenum InFormat)
{
	glBindImageTexture(InUnit, 
					Texture, 
					InLevel, 
					InLayered, 
					InLayer, 
					InAccess, 
					InFormat);
}