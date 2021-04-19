#pragma once
#ifndef __GOWRENDERBUFFER_H__
#define __GOWRENDERBUFFER_H__

#include "GOWEngine.h"

namespace GOW
{
	// GOWRenderBuffer
	// ������Ⱦ����
	class GOWRenderBuffer
	{
	public:
		// ������
		uint32 Width;
		
		// ����߶�
		uint32 Height;

		// ��Ⱦ��������
		GLuint Buffer;

	public:
		EXPORT GOWRenderBuffer();

		// InWidth ������
		// InHeight ����߶�
		// InFormat �����ڲ���ʽ
		EXPORT GOWRenderBuffer(uint32 InWidth, uint32 InHeight, GLenum InFormat);

		EXPORT ~GOWRenderBuffer();

		// ����Ⱦ����
		EXPORT void Bind();

		// �����Ⱦ����
		EXPORT void UnBind();

		// ������Ⱦ�����ʽ
		// InFormat �����ڲ���ʽ
		EXPORT void SetFormat(GLenum InForamt);

		// ������Ⱦ������
		// InWidth ������
		// InHeight ����߶�
		EXPORT void SetSize(uint32 InWidth, uint32 InHeight);
	private:
		GLenum Format;
	};
};

#endif
