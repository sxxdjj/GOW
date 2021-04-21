#include "GOWFrameBuffer.h"

using namespace GOW;

int32 GOWFrameBuffer::MaxColorAttachments = 0;

GOWFrameBuffer::GOWFrameBuffer(GLenum InTarget /* = GL_FRAMEBUFFER */)
{
	Target = InTarget;
	Width = 0;
	Heigth = 0;

	glGenFramebuffers(1, &Buffer);

	if (MaxColorAttachments == 0)
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &MaxColorAttachments);
}

GOWFrameBuffer::~GOWFrameBuffer()
{
	glDeleteFramebuffers(1, &Buffer);
}

GLenum GOWFrameBuffer::GetBufferStatus()
{
	Bind();
	GLenum Ret = glCheckFramebufferStatus(Target);
	UnBind();

	return Ret;
}

void GOWFrameBuffer::Bind()
{
	glBindFramebuffer(Target, Buffer);
}

void GOWFrameBuffer::Bind(GLenum InTarget)
{
	glBindFramebuffer(InTarget, Buffer);

	if (DrawBuffers.size() != 0)
		glDrawBuffers(DrawBuffers.size(), DrawBuffers.data());
	else
		glDrawBuffer(GL_NONE);
}

void GOWFrameBuffer::UnBind()
{
	glBindFramebuffer(Target, 0);
}

bool GOWFrameBuffer::AttachTexture(GLenum InAttachment, GOWTexture& InTexture)
{
	if (Width == 0 && Heigth == 0)
	{
		Width = InTexture.Width;
		Heigth = InTexture.Height;
	}
	else if (Width != InTexture.Width || Heigth != InTexture.Height)
	{
		GOWEngine::ErrorString.push_back("The size of the texture does not "
			"match the size of previously attached textures or "
			"renderbuffers.");

		return false;
	}

	Bind();
	glFramebufferTexture(Target, InAttachment, InTexture.Texture, 0);
	UnBind();

	GLenum AttachmentMax = GL_COLOR_ATTACHMENT0 + MaxColorAttachments;

	switch (InAttachment)
	{
	case GL_NONE:
	case GL_FRONT_LEFT:
	case GL_FRONT_RIGHT:
	case GL_BACK_LEFT:
	case GL_BACK_RIGHT:
		DrawBuffers.push_back(InAttachment);
		break;
	default:
		if (InAttachment >= GL_COLOR_ATTACHMENT0 && InAttachment < AttachmentMax)
			DrawBuffers.push_back(InAttachment);
		break;
	}

	return true;
}

bool GOWFrameBuffer::AttachTextureLayer(GLenum InAttachment, GOWTexture& InTexture, uint32 InLayer)
{
	if (Width == 0 && Heigth == 0)
	{
		Width = InTexture.Width;
		Heigth = InTexture.Height;
	}
	else if (Width != InTexture.Width || Heigth != InTexture.Height)
	{
		GOWEngine::ErrorString.push_back("The size of the texture does not "
			"match the size of previously attached textures or "
			"renderbuffers.");

		return false;
	}

	if (InLayer >= InTexture.NumLayers)
	{
		GOWEngine::ErrorString.push_back("Layer argument is exceeding the"
			" number of layers of the texture");

		return false;
	}

	Bind();
	glFramebufferTextureLayer(Target, InAttachment, InTexture.Texture, 0, InLayer);
	UnBind();

	GLenum AttachmentMax = GL_COLOR_ATTACHMENT0 + MaxColorAttachments;

	switch (AttachmentMax)
	{
	case GL_NONE:
	case GL_FRONT_LEFT:
	case GL_FRONT_RIGHT:
	case GL_BACK_LEFT:
	case GL_BACK_RIGHT:
		DrawBuffers.push_back(InAttachment);
		break;
	default:
		if (InAttachment >= GL_COLOR_ATTACHMENT0 && InAttachment < AttachmentMax)
			DrawBuffers.push_back(InAttachment);
		break;
	}

	return true;
}

bool GOWFrameBuffer::AttachRenderBuffer(GLenum InAttachment, GOWRenderBuffer& InBuffer)
{
	if (Width == 0 && Heigth == 0)
	{
		Width = InBuffer.Width;
		Heigth = InBuffer.Height;
	}
	else if (Width != InBuffer.Width || Heigth != InBuffer.Height)
	{
		GOWEngine::ErrorString.push_back("The size of the renderbuffer does not "
			"match the size of previously attached textures or "
			"renderbuffers.");

		return false;
	}

	Bind();
	glFramebufferRenderbuffer(Target, InAttachment, GL_RENDERBUFFER, InBuffer.Buffer);
	UnBind();

	GLenum AttachmentMax = GL_COLOR_ATTACHMENT0 + MaxColorAttachments;

	switch (InAttachment)
	{
	case GL_NONE:
	case GL_FRONT_LEFT:
	case GL_FRONT_RIGHT:
	case GL_BACK_LEFT:
	case GL_BACK_RIGHT:
		DrawBuffers.push_back(InAttachment);
		break;
	default:
		if (InAttachment >= GL_COLOR_ATTACHMENT0 && InAttachment < AttachmentMax)
			DrawBuffers.push_back(InAttachment);
		break;
	}

	return true;
}

void GOWFrameBuffer::Finalize()
{
	Bind();
	if (DrawBuffers.size() != 0)
		glDrawBuffers(DrawBuffers.size(), DrawBuffers.data());
	else
		glDrawBuffer(GL_NONE);
	UnBind();
}

void GOWFrameBuffer::BlitTo(GOW::GOWFrameBuffer* InTarget,
							uint32 InSrcX0,
							uint32 InSrcY0,
							uint32 InSrcX1,
							uint32 InSrcY1,
							uint32 InDstX0,
							uint32 InDstY0,
							uint32 InDstX1,
							uint32 InDstY1,
							GLbitfield InMask,
							GLenum InFilter)
{
	if (InTarget)
		InTarget->Bind(GL_DRAW_BUFFER);
	else
		glBindFramebuffer(GL_DRAW_BUFFER, 0);

	Bind(GL_READ_FRAMEBUFFER);
	glBlitFramebuffer(InSrcX0,
					InSrcY0,
					InSrcX1,
					InSrcY1,
					InDstX0,
					InDstY0,
					InDstX1,
					InDstY1,
					InMask,
					InFilter);
	UnBind();

	if (InTarget)
		InTarget->UnBind();
}

void GOWFrameBuffer::BlitFromDefault(uint32 InSrcX0,
									uint32 InSrcY0,
									uint32 InSrcX1,
									uint32 InSrcY1,
									uint32 InDstX0,
									uint32 InDstY0,
									uint32 InDstX1,
									uint32 InDstY1,
									GLbitfield InMask,
									GLenum InFilter)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	Bind(GL_DRAW_FRAMEBUFFER);
	glBlitFramebuffer(InSrcX0, 
					InSrcY0, 
					InSrcX1, 
					InSrcY1,
					InDstX0, 
					InDstY0, 
					InDstX1, 
					InDstY1, 
					InMask, 
					InFilter);
	UnBind();
}