#pragma once
#include "GOWEngine.h"

namespace GOW
{
	// class GOWImage
	// ����ͼƬ
	class GOWImage
	{
	public:
		// ���һ��·�����б�����ͼƬ�ļ�����
		// InPath ��ӵ��б��·��
		// Ϊ�˱����ظ���ӣ���Ҫ�ж��Ƿ��ǵ�һ�����
		EXPORT static void AddPath(std::string InPath);

		EXPORT GOWImage();

		// ͨ���ļ�������һ��ͼƬ
		EXPORT GOWImage(std::string InFileName);

		// InWidth ͼƬ���
		// InHeight ͼƬ�߶�
		// InBytesPerPixel �������صĴ�С
		// InData �������ݵ�ָ��
		EXPORT GOWImage(uint32 InWidth, uint32 InHeight, uint32 InBytesPerPixel);
		EXPORT ~GOWImage();

		// ����һ���յ�ͼƬ
		// InWidth ͼƬ���
		// InHeight ͼƬ�߶�
		// �ɹ�����true������false
		EXPORT bool CreateEmpty(uint32 InWidth, uint32 InHeight);

		// ����һ����ͼƬ�ļ�
		// InFileName ����ͼƬ��·��
		// �ɹ�����true������false
		EXPORT bool Load(const std::string& InFileName);

		// ͨ���������ݼ���һ��ͼƬ
		// InWidth ͼƬ���
		// InHeight ͼƬ�߶�
		// InBytesPixel �������صĴ�С
		// InData ͼƬ����ָ��
		// �ɹ�����true�����򷵻�false
		// ͼƬ����´��һ���������ڼ���ͼƬ
		EXPORT bool Load(uint32 InWidth, uint32 InHeight, uint32 InBytesPerPixel, void* InData);

		// �洢ͼƬ�ļ�
		// InFileName ͼƬ�洢��·��
		// �ɹ�����true������false
		EXPORT bool Save(const std::string& InFileName);

		// ����һ��ͼƬ����ǰͼƬ����
		// InSrc ԭͼƬ
		// InX ����ͼƬʱX����
		// InY ����ͼƬʱY����
		EXPORT bool CopyFrom(const GOWImage& InSrc, int32 InX, int32 InY);

		// ����һ��ͼƬ����ǰͼƬ����
		// InSrc ԭͼƬ
		// InDstRect Ŀ��ͼƬ����
		EXPORT bool CopyFrom(const GOWImage& InSrc, SDL_Rect& InDstRect);

		// ����һ��ͼƬ����ǰͼƬ����
		// InSrc ԭͼƬ
		// InDstRect Ŀ��ͼƬ����
		// InSrcRect ԭͼƬ����
		EXPORT bool CopyFrom(const GOWImage& InSrc, SDL_Rect& InDstRect, const SDL_Rect& InSrcRect);

		// ��x�ᷭתͼƬ
		EXPORT void VerticalFlip();

		// ��Y�ᷭתͼƬ
		EXPORT void HorizontalFlip();
	public:
		// ͼƬ�Ŀ��
		uint32 Width;

		// ͼƬ�ĸ߶�
		uint32 Height;

		// ���������ֽ���
		uint32 BytesPerPixel;

		// ͼƬ����
		void* Data;

		// ͼƬ����
		SDL_Surface* Image;

	private:
		bool FreeData;
		static std::vector<std::string> Paths;
	};
};