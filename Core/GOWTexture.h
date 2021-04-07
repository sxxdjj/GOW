#pragma once
#ifndef __GOWTEXTURE_H__
#define __GOWTEXTURE_H__

#include "GOWEngine.h"
#include "GOWImage.h"

namespace GOW
{
	// class GOWTexture
	// ��������
	class GOWTexture
	{
	public:
		EXPORT GOWTexture();
		EXPORT ~GOWTexture();

		// ���һ��ͼƬ·����·���б�
		// InPath ͼƬ·��
		// �����ظ���ӣ���Ҫ����ӵ�ʱ����Ψһ��
		EXPORT static void AddPath(std::string InPath);

		// �洢һ����������ڲ�map�У�����map�е����������Ψһ��
		// InName map�е�key
		// InTexture �������
		// �ɹ�����true������false
		EXPORT static bool StoreTexture(std::string InName, std::shared_ptr<GOWTexture> InTexture);

		// ͨ��key������Ӧ���������
		// InName ������������key
		// ����һ����Ӧ��������ָ�룬���û�ҵ�����һ��nullptr
		EXPORT static std::shared_ptr<GOWTexture> FindTexture(std::string InName);

		// ��һ��������Ӧ��shader
		// InTextureUnit �󶨵�����Ԫ
		virtual void Bind(uint32 InTextureUnit = 0) = 0;

		// ���һ������
		// InTextureUnit ��������Ԫ
		virtual void UnBind(uint32 InTextureUnit = 0) = 0;

		// �����������
		// InName �����������
		// InParameter �������
		EXPORT void SetParameter(GLenum InName, int InParameter);

		// �����������
		// InName �����������
		// InParameter �������
		EXPORT void SetParameter(GLenum InName, float InParameter);

		// ��һ������㼶����ͼƬ��Ԫ
		// InUnit ͼƬ��Ԫ������
		// InLevel �����minmap�ȼ�
		// InLayered GL_FALSE����������һ��layer�󶨵�ͼƬ��Ԫ��GL_True��������󶨵�ͼƬ��Ԫ
		// InLayer ���InLayered=GL_FALSE,ָ��layer�󶨵�ͼƬ��Ԫ���������
		// InAceese ͼƬ���ݵķ��ʷ�ʽ������GL_READ_ONLY, GL_WRITE_ONLY, GL_READ_WRITE
		// InFormat ͼƬ���ݸ�ʽ������GL_RGBA8, GL_RGBA32F
		EXPORT void BindImage(GLuint InUnit, 
							GLint InLevel,
							GLboolean InLayered, 
							GLint InLayer, 
							GLenum InAccess, 
							GLenum InFormat);
	public:
		// ����Ŀ��
		GLenum Target;

		// ��������
		GLuint Texture;

		// ������
		uint32 Width;

		// ����߶�
		uint32 Height;

		// �㼶����
		uint32 NumLayers;
	protected:
		// ���������
		EXPORT static std::map<std::string, std::shared_ptr<GOWTexture>> Textures;
	};
};

#endif