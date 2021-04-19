#include "GOWRenderBuffer.h"

using namespace GOW;

GOWRenderBuffer::GOWRenderBuffer()
{
	Format = GL_FLOAT;
	Width = 100;
	Height = 100;

	glGenRenderbuffers(1, &Buffer);
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, Format, Width, Height);
	UnBind();
}

GOWRenderBuffer::GOWRenderBuffer(uint32 InWidth, uint32 InHeight, GLenum InFormat)
{
	Format = InFormat;
	Width = InWidth;
	Height = InHeight;

	glGenRenderbuffers(1, &Buffer);
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, Format, Width, Height);
	UnBind();
}

GOWRenderBuffer::~GOWRenderBuffer()
{
	glDeleteRenderbuffers(1, &Buffer);
}

void GOWRenderBuffer::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, Buffer);
}

void GOWRenderBuffer::UnBind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void GOWRenderBuffer::SetFormat(GLenum InForamt)
{
	Format = InForamt;

	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, InForamt, Width, Height);
	UnBind();
}

void GOWRenderBuffer::SetSize(uint32 InWidth, uint32 InHeight)
{
	Width = InWidth;
	Height = InHeight;
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, Format, Width, Height);
	UnBind();
}