#pragma once
#ifndef __GOWFRAMEBUFFER_H__
#define __GOWFRAMEBUFFER_H__

#include "GOWEngine.h"
#include "GOWTexture.h"
#include "GOWRenderBuffer.h"

namespace GOW
{
	// GOWFrameBuffer
	// 管理帧缓冲
	class GOWFrameBuffer
	{
	public:
		// InTarget 缓冲目标
		EXPORT GOWFrameBuffer(GLenum InTarget = GL_FRAMEBUFFER);
		EXPORT ~GOWFrameBuffer();

		// 检查帧缓冲完成状态
		// 返回帧缓冲状态
		EXPORT GLenum GetBufferStatus();

		// 绑定帧缓冲目标
		EXPORT void Bind();

		// 绑定帧缓冲目标
		// InTarget 缓冲目标
		EXPORT void Bind(GLenum InTarget);

		// 重置为默认缓冲帧
		EXPORT void UnBind();

		// 附加纹理到帧缓冲
		// InAttachment 纹理的附件点
		// InTexture 附加的纹理
		// 成功返回true，否则返回false
		EXPORT bool AttachTexture(GLenum InAttachment, GOWTexture& InTexture);

		// 附加纹理层级到帧缓冲
		// InAttachment 纹理的附件点
		// InTexture 附加的纹理
		// InLayer 附加的层级
		// 成功返回true，否则返回false
		EXPORT bool AttachTextureLayer(GLenum InAttachment, GOWTexture& InTexture, uint32 InLayer);

		// 附加渲染缓冲到帧缓冲
		// InAttachment 渲染缓冲附件点
		// InBuffer 附加的渲染缓冲
		// 成功返回true，否则返回false
		EXPORT bool AttachRenderBuffer(GLenum InAttachment, GOWRenderBuffer& InBuffer);

		// 设置绘制缓冲
		EXPORT void Finalize();

		// 复制帧缓冲中一块像素到另一个帧缓冲里
		// InTarget 目标缓冲, 如果是空指针，那就复制到默认帧缓冲中
		// InSrcX0, InSrcY0, InSrcX1, InSrcY1, 原缓冲像素块位置和大小
		// InDstX0, InDstY0, InDstX1, InDstY1, 目标缓冲像素块位置和大小
		// InMask 掩码标记，哪种缓冲被拷贝，标记包括：GL_COLOR_BUFFER_BIT,
		// GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
		// InFilter 图片插值方式,包括GL_NEAREST和GL_LINEAR
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

		// 复制默认帧缓冲中一块像素到当前帧缓冲里
		// InSrcX0, InSrcY0, InSrcX1, InSrcY1, 默认帧缓冲像素块位置和大小
		// InDstX0, InDstY0, InDstX1, InDstY1, 当前帧缓冲像素块位置和大小
		// InMask 掩码标记，哪种缓冲被拷贝，标记包括：GL_COLOR_BUFFER_BIT,
		// GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
		// InFilter 图片插值方式,包括GL_NEAREST和GL_LINEAR
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