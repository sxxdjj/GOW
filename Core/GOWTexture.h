#pragma once
#ifndef __GOWTEXTURE_H__
#define __GOWTEXTURE_H__

#include "GOWEngine.h"
#include "GOWImage.h"

namespace GOW
{
	// class GOWTexture
	// 管理纹理
	class GOWTexture
	{
	public:
		EXPORT GOWTexture();
		EXPORT ~GOWTexture();

		// 添加一个图片路径到路径列表
		// InPath 图片路径
		// 避免重复添加，需要在添加的时候检查唯一性
		EXPORT static void AddPath(std::string InPath);

		// 存储一个纹理对象到内部map中，并且map中的纹理对象都是唯一的
		// InName map中的key
		// InTexture 纹理对象
		// 成功返回true，否则false
		EXPORT static bool StoreTexture(std::string InName, std::shared_ptr<GOWTexture> InTexture);

		// 通过key查找相应的纹理对象
		// InName 查找纹理对象的key
		// 返回一个对应纹理对象的指针，如果没找到返回一个nullptr
		EXPORT static std::shared_ptr<GOWTexture> FindTexture(std::string InName);

		// 绑定一个纹理到相应的shader
		// InTextureUnit 绑定的纹理单元
		virtual void Bind(uint32 InTextureUnit = 0) = 0;

		// 解绑一个纹理
		// InTextureUnit 解绑的纹理单元
		virtual void UnBind(uint32 InTextureUnit = 0) = 0;

		// 设置纹理参数
		// InName 纹理参数名字
		// InParameter 纹理参数
		EXPORT void SetParameter(GLenum InName, int InParameter);

		// 设置纹理参数
		// InName 纹理参数名字
		// InParameter 纹理参数
		EXPORT void SetParameter(GLenum InName, float InParameter);

		// 绑定一个纹理层级到到图片单元
		// InUnit 图片单元的索引
		// InLevel 纹理的minmap等级
		// InLayered GL_FALSE纹理数组中一个layer绑定到图片单元，GL_True整个数组绑定到图片单元
		// InLayer 如果InLayered=GL_FALSE,指定layer绑定到图片单元，否则忽略
		// InAceese 图片数据的访问方式，包括GL_READ_ONLY, GL_WRITE_ONLY, GL_READ_WRITE
		// InFormat 图片数据格式，比如GL_RGBA8, GL_RGBA32F
		EXPORT void BindImage(GLuint InUnit, 
							GLint InLevel,
							GLboolean InLayered, 
							GLint InLayer, 
							GLenum InAccess, 
							GLenum InFormat);
	public:
		// 纹理目标
		GLenum Target;

		// 纹理名字
		GLuint Texture;

		// 纹理宽度
		uint32 Width;

		// 纹理高度
		uint32 Height;

		// 层级数量
		uint32 NumLayers;
	protected:
		// 储存的纹理
		EXPORT static std::map<std::string, std::shared_ptr<GOWTexture>> Textures;
	};

	// class GOWTexture1D
	// 管理一维纹理
	class GOWTexture1D : public GOWTexture
	{
	public:
		EXPORT GOWTexture1D();

		// InPath 图片文件路径
		EXPORT GOWTexture1D(const std::string& InPath);

		// InImage 用于纹理的图片
		EXPORT GOWTexture1D(const GOW::GOWImage& InImage);

		// InRes 纹理分辨率
		// InInternalFormat 纹理内部格式
		// InType 像素类型
		// InFormat 纹理格式
		EXPORT GOWTexture1D(uint32 InRes, GLenum InInternalFormat, GLenum InType, GLenum InFormat);

		EXPORT ~GOWTexture1D();

		// 创建一个空纹理
		// InRes 纹理分辨率
		// InInternalFormat 纹理内部格式
		// InType 像素类型
		// InFormat 纹理格式
		EXPORT void CreateEmpty(uint32 InRes, GLenum InInternalFormat, GLenum InType, GLenum InFormat);

		// 纹理加载一张新图片
		// InImage 用于纹理的图片
		EXPORT bool Load(const GOW::GOWImage& InImage);

		// 纹理加载一张新图片
		// InPath 图片路径
		EXPORT bool Load(const std::string& InPath);

		// 绑定纹理到指定的着色器
		// InTextureUnit 纹理单元
		EXPORT void Bind(uint32 InTextureUnit = 0);

		// 解绑纹理
		EXPORT void UnBind(uint32 InTextureUnit = 0);
	};

	// GOWTexture1DArray
	// 管理1维纹理数组
	class GOWTexture1DArray : public GOWTexture
	{
	public:
		EXPORT GOWTexture1DArray();

		// InPaths 图片路径
		EXPORT GOWTexture1DArray(const std::vector<std::string>& InPaths);

		// InImages 纹理层级的图片
		EXPORT GOWTexture1DArray(const std::vector<GOW::GOWImage>& InImages);

		// InRes 纹理分辨率
		// InNumLayers 层级数量
		// InInternalFormat 纹理内部格式
		// InType 像素类型
		// InFormat 纹理格式
		EXPORT GOWTexture1DArray(uint32 InRes,
								uint32 InNumLayers,
								GLenum InInternalFormat, 
								GLenum InType, 
								GLenum InFormat);

		EXPORT ~GOWTexture1DArray();

		// 创建一个空的纹理
		// InNumLayers 层级数量
		// InInternalFormat 纹理内部格式
		// InType 像素类型
		// InFormat 纹理格式
		EXPORT void CreateEmpty(uint32 InRes, 
								uint32 InNumLayers, 
								GLenum InInternalFormat,
								GLenum InType, 
								GLenum InFormat);

		// 纹理加载一张新图片
		// InImage 用于纹理的图片
		EXPORT bool Load(const std::vector<GOW::GOWImage>& InImages);

		// 纹理加载一张新图片
		// InPath 图片路径
		EXPORT bool Load(const std::vector<std::string>& InPaths);

		// 绑定纹理到指定的着色器
		// InTextureUnit 纹理单元
		EXPORT void Bind(uint32 InTextureUnit  = 0);

		// 解绑纹理
		EXPORT void UnBind(uint32 InTextureUnit = 0);
	};

	// class GOWTexture2D
	// 管理2维纹理
	class GOWTexture2D : public GOWTexture
	{
	public:
		EXPORT GOWTexture2D();

		// InPath 图片文件路径
		EXPORT GOWTexture2D(const std::string& InPath);

		// InImage 用于纹理的图片
		EXPORT GOWTexture2D(const GOW::GOWImage& InImage);

		// InResX 纹理x方向分辨率
		// InResY 纹理Y方向分辨率
		// InInternalFormat 纹理内部格式
		// InType 像素类型
		// InFormat 纹理格式
		EXPORT GOWTexture2D(uint32 InResX, 
							uint32 InResY, 
							GLenum InIternalFormat, 
							GLenum InType, 
							GLenum InFormat);

		EXPORT ~GOWTexture2D();

		// 创建一个空的纹理
		// InResX 纹理x方向分辨率
		// InResY 纹理Y方向分辨率
		// InInternalFormat 纹理内部格式
		// InType 像素类型
		// InFormat 纹理格式
		EXPORT void CreateEmpty(uint32 InResX,
								uint32 InResY,
								GLenum InInteranlFormat,
								GLenum InType,
								GLenum InFormat);

		// 纹理加载一个新的图片
		// InImage 用于纹理的图片
		EXPORT bool Load(const GOW::GOWImage& InImage);

		// 纹理加载一个新的图片
		// InPath 图片文件路径
		EXPORT bool Load(const std::string& InPath);

		// 绑定纹理，用于着色器
		// InTexureUnit 纹理单元
		EXPORT void Bind(uint32 InTextureUnit = 0);

		// 解绑纹理
		// InTexureUnit 纹理单元
		EXPORT void UnBind(uint32 InTextureUnit = 0);
	};
};

#endif