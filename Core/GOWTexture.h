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

	// class GOWTexture1D
	// ����һά����
	class GOWTexture1D : public GOWTexture
	{
	public:
		EXPORT GOWTexture1D();

		// InPath ͼƬ�ļ�·��
		EXPORT GOWTexture1D(const std::string& InPath);

		// InImage ���������ͼƬ
		EXPORT GOWTexture1D(const GOW::GOWImage& InImage);

		// InRes ����ֱ���
		// InInternalFormat �����ڲ���ʽ
		// InType ��������
		// InFormat �����ʽ
		EXPORT GOWTexture1D(uint32 InRes, GLenum InInternalFormat, GLenum InType, GLenum InFormat);

		EXPORT ~GOWTexture1D();

		// ����һ��������
		// InRes ����ֱ���
		// InInternalFormat �����ڲ���ʽ
		// InType ��������
		// InFormat �����ʽ
		EXPORT void CreateEmpty(uint32 InRes, GLenum InInternalFormat, GLenum InType, GLenum InFormat);

		// �������һ����ͼƬ
		// InImage ���������ͼƬ
		EXPORT bool Load(const GOW::GOWImage& InImage);

		// �������һ����ͼƬ
		// InPath ͼƬ·��
		EXPORT bool Load(const std::string& InPath);

		// ������ָ������ɫ��
		// InTextureUnit ����Ԫ
		EXPORT void Bind(uint32 InTextureUnit = 0);

		// �������
		EXPORT void UnBind(uint32 InTextureUnit = 0);
	};

	// GOWTexture1DArray
	// ����1ά��������
	class GOWTexture1DArray : public GOWTexture
	{
	public:
		EXPORT GOWTexture1DArray();

		// InPaths ͼƬ·��
		EXPORT GOWTexture1DArray(const std::vector<std::string>& InPaths);

		// InImages ����㼶��ͼƬ
		EXPORT GOWTexture1DArray(const std::vector<GOW::GOWImage>& InImages);

		// InRes ����ֱ���
		// InNumLayers �㼶����
		// InInternalFormat �����ڲ���ʽ
		// InType ��������
		// InFormat �����ʽ
		EXPORT GOWTexture1DArray(uint32 InRes,
								uint32 InNumLayers,
								GLenum InInternalFormat, 
								GLenum InType, 
								GLenum InFormat);

		EXPORT ~GOWTexture1DArray();

		// ����һ���յ�����
		// InNumLayers �㼶����
		// InInternalFormat �����ڲ���ʽ
		// InType ��������
		// InFormat �����ʽ
		EXPORT void CreateEmpty(uint32 InRes, 
								uint32 InNumLayers, 
								GLenum InInternalFormat,
								GLenum InType, 
								GLenum InFormat);

		// �������һ����ͼƬ
		// InImage ���������ͼƬ
		EXPORT bool Load(const std::vector<GOW::GOWImage>& InImages);

		// �������һ����ͼƬ
		// InPath ͼƬ·��
		EXPORT bool Load(const std::vector<std::string>& InPaths);

		// ������ָ������ɫ��
		// InTextureUnit ����Ԫ
		EXPORT void Bind(uint32 InTextureUnit  = 0);

		// �������
		EXPORT void UnBind(uint32 InTextureUnit = 0);
	};

	// class GOWTexture2D
	// ����2ά����
	class GOWTexture2D : public GOWTexture
	{
	public:
		EXPORT GOWTexture2D();

		// InPath ͼƬ�ļ�·��
		EXPORT GOWTexture2D(const std::string& InPath);

		// InImage ���������ͼƬ
		EXPORT GOWTexture2D(const GOW::GOWImage& InImage);

		// InResX ����x����ֱ���
		// InResY ����Y����ֱ���
		// InInternalFormat �����ڲ���ʽ
		// InType ��������
		// InFormat �����ʽ
		EXPORT GOWTexture2D(uint32 InResX, 
							uint32 InResY, 
							GLenum InIternalFormat, 
							GLenum InType, 
							GLenum InFormat);

		EXPORT ~GOWTexture2D();

		// ����һ���յ�����
		// InResX ����x����ֱ���
		// InResY ����Y����ֱ���
		// InInternalFormat �����ڲ���ʽ
		// InType ��������
		// InFormat �����ʽ
		EXPORT void CreateEmpty(uint32 InResX,
								uint32 InResY,
								GLenum InInteranlFormat,
								GLenum InType,
								GLenum InFormat);

		// �������һ���µ�ͼƬ
		// InImage ���������ͼƬ
		EXPORT bool Load(const GOW::GOWImage& InImage);

		// �������һ���µ�ͼƬ
		// InPath ͼƬ�ļ�·��
		EXPORT bool Load(const std::string& InPath);

		// ������������ɫ��
		// InTexureUnit ����Ԫ
		EXPORT void Bind(uint32 InTextureUnit = 0);

		// �������
		// InTexureUnit ����Ԫ
		EXPORT void UnBind(uint32 InTextureUnit = 0);
	};
};

#endif