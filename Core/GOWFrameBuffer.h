#pragma once
#ifndef __GOWFRAMEBUFFER_H__
#define __GOWFRAMEBUFFER_H__

#include "GOWEngine.h"
#include "GOWTexture.h"
#include "GOWRenderBuffer.h"

namespace GOW
{
	// GOWFrameBuffer
	// ����֡����
	class GOWFrameBuffer
	{
	public:
		// InTarget ����Ŀ��
		EXPORT GOWFrameBuffer(GLenum InTarget = GL_FRAMEBUFFER);
		EXPORT ~GOWFrameBuffer();

		// ���֡�������״̬
		// ����֡����״̬
		EXPORT GLenum GetBufferStatus();

		// ��֡����Ŀ��
		EXPORT void Bind();

		// ��֡����Ŀ��
		// InTarget ����Ŀ��
		EXPORT void Bind(GLenum InTarget);

		// ����ΪĬ�ϻ���֡
		EXPORT void UnBind();

		// ��������֡����
		// InAttachment ����ĸ�����
		// InTexture ���ӵ�����
		// �ɹ�����true�����򷵻�false
		EXPORT bool AttachTexture(GLenum InAttachment, GOWTexture& InTexture);

		// ��������㼶��֡����
		// InAttachment ����ĸ�����
		// InTexture ���ӵ�����
		// InLayer ���ӵĲ㼶
		// �ɹ�����true�����򷵻�false
		EXPORT bool AttachTextureLayer(GLenum InAttachment, GOWTexture& InTexture, uint32 InLayer);

		// ������Ⱦ���嵽֡����
		// InAttachment ��Ⱦ���帽����
		// InBuffer ���ӵ���Ⱦ����
		// �ɹ�����true�����򷵻�false
		EXPORT bool AttachRenderBuffer(GLenum InAttachment, GOWRenderBuffer& InBuffer);

		// ���û��ƻ���
		EXPORT void Finalize();

		// ����֡������һ�����ص���һ��֡������
		// InTarget Ŀ�껺��, ����ǿ�ָ�룬�Ǿ͸��Ƶ�Ĭ��֡������
		// InSrcX0, InSrcY0, InSrcX1, InSrcY1, ԭ�������ؿ�λ�úʹ�С
		// InDstX0, InDstY0, InDstX1, InDstY1, Ŀ�껺�����ؿ�λ�úʹ�С
		// InMask �����ǣ����ֻ��屻��������ǰ�����GL_COLOR_BUFFER_BIT,
		// GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
		// InFilter ͼƬ��ֵ��ʽ,����GL_NEAREST��GL_LINEAR
		EXPORT void BlitTo(GOW::GOWFrameBuffer* InTarget,
						uint32 InSrcX0, 
						uint32 InSrcY0, 
						uint32 InSrcX1, 
						uint32 InSrcY1, 
						uint32 InDstX0,
						uint32 InDstY0, 
						uint32 InDstX1, 
						uint32 InDstY1,
						GLbitfield InMask,
						GLenum InFilter);

		// ����Ĭ��֡������һ�����ص���ǰ֡������
		// InSrcX0, InSrcY0, InSrcX1, InSrcY1, Ĭ��֡�������ؿ�λ�úʹ�С
		// InDstX0, InDstY0, InDstX1, InDstY1, ��ǰ֡�������ؿ�λ�úʹ�С
		// InMask �����ǣ����ֻ��屻��������ǰ�����GL_COLOR_BUFFER_BIT,
		// GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
		// InFilter ͼƬ��ֵ��ʽ,����GL_NEAREST��GL_LINEAR
		EXPORT void BlitFromDefault(uint32 InSrcX0, 
									uint32 InSrcY0, 
									uint32 InSrcX1, 
									uint32 InSrcY1, 
									uint32 InDstX0, 
									uint32 InDstY0, 
									uint32 InDstX1, 
									uint32 InDstY1, 
									GLbitfield InMask, 
									GLenum InFilter);
	private:
		GLuint Buffer;
		GLenum Target;
		uint32 Width;
		uint32 Heigth;
		std::vector<GLenum> DrawBuffers;

		static int32 MaxColorAttachments;
	};
};
#endif