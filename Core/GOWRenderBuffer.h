#pragma once
#ifndef __GOWRENDERBUFFER_H__
#define __GOWRENDERBUFFER_H__

#include "GOWEngine.h"

namespace GOW
{
	// GOWRenderBuffer
	// 管理渲染缓冲
	class GOWRenderBuffer
	{
	public:
		// 缓冲宽度
		uint32 Width;
		
		// 缓冲高度
		uint32 Height;

		// 渲染缓冲名字
		GLuint Buffer;

	public:
		EXPORT GOWRenderBuffer();

		// InWidth 缓冲宽度
		// InHeight 缓冲高度
		// InFormat 缓冲内部格式
		EXPORT GOWRenderBuffer(uint32 InWidth, uint32 InHeight, GLenum InFormat);

		EXPORT ~GOWRenderBuffer();

		// 绑定渲染缓冲
		EXPORT void Bind();

		// 解绑渲染缓冲
		EXPORT void UnBind();

		// 设置渲染缓冲格式
		// InFormat 缓冲内部格式
		EXPORT void SetFormat(GLenum InForamt);

		// 设置渲染缓冲宽高
		// InWidth 缓冲宽度
		// InHeight 缓冲高度
		EXPORT void SetSize(uint32 InWidth, uint32 InHeight);
	private:
		GLenum Format;
	};
};

#endif
