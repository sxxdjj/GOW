#pragma once
#include "GOWEngine.h"

namespace GOW
{
	// class GOWImage
	// 管理图片
	class GOWImage
	{
	public:
		// 添加一个路径到列表，用于图片文件搜素
		// InPath 添加到列表的路径
		// 为了避免重复添加，需要判断是否是第一次添加
		EXPORT static void AddPath(std::string InPath);

		EXPORT GOWImage();

		// 通过文件名加载一个图片
		EXPORT GOWImage(std::string InFileName);

		// InWidth 图片宽度
		// InHeight 图片高度
		// InBytesPerPixel 单个像素的大小
		// InData 缓冲数据的指针
		EXPORT GOWImage(uint32 InWidth, uint32 InHeight, uint32 InBytesPerPixel);
		EXPORT ~GOWImage();

		// 创建一个空的图片
		// InWidth 图片宽度
		// InHeight 图片高度
		// 成功返回true，否则false
		EXPORT bool CreateEmpty(uint32 InWidth, uint32 InHeight);

		// 加载一个新图片文件
		// InFileName 加载图片的路径
		// 成功返回true，否则false
		EXPORT bool Load(const std::string& InFileName);

		// 通过缓存数据加载一个图片
		// InWidth 图片宽度
		// InHeight 图片高度
		// InBytesPixel 单个像素的大小
		// InData 图片数据指针
		// 成功返回true，否则返回false
		// 图片对象会拷贝一份数据用于加载图片
		EXPORT bool Load(uint32 InWidth, uint32 InHeight, uint32 InBytesPerPixel, void* InData);

		// 存储图片文件
		// InFileName 图片存储的路径
		// 成功返回true，否则false
		EXPORT bool Save(const std::string& InFileName);

		// 拷贝一个图片到当前图片对象
		// InSrc 原图片
		// InX 拷贝图片时X坐标
		// InY 拷贝图片时Y坐标
		EXPORT bool CopyFrom(const GOWImage& InSrc, int32 InX, int32 InY);

		// 拷贝一个图片到当前图片对象
		// InSrc 原图片
		// InDstRect 目标图片区域
		EXPORT bool CopyFrom(const GOWImage& InSrc, SDL_Rect& InDstRect);

		// 拷贝一个图片到当前图片对象
		// InSrc 原图片
		// InDstRect 目标图片区域
		// InSrcRect 原图片区域
		EXPORT bool CopyFrom(const GOWImage& InSrc, SDL_Rect& InDstRect, const SDL_Rect& InSrcRect);

		// 沿x轴翻转图片
		EXPORT void VerticalFlip();

		// 沿Y轴翻转图片
		EXPORT void HorizontalFlip();
	public:
		// 图片的宽度
		uint32 Width;

		// 图片的高度
		uint32 Height;

		// 单个像素字节数
		uint32 BytesPerPixel;

		// 图片数据
		void* Data;

		// 图片表面
		SDL_Surface* Image;

	private:
		bool FreeData;
		static std::vector<std::string> Paths;
	};
};