#pragma once
#ifndef __GOWENGINE_H__
#define __GOWENGINE_H__

// ��ӡOpenGL������Ϣ��ʹ�ô˺������ļ�������Ӧ������
#define CHEK_GL_ERROR(message) do{\
	GOW::GOWEngine::CheckError(message, __FILE__, __LINE__);\
}while(0)

#ifdef _WIN32
	#ifdef MAKE_LIB // ����GOW
		#ifdef MAKE_DLL // dynamic
			#define EXPORT __declspec(dllexport)
		#elif MAKE_STATIC // static
			#define  EXPORT
		#endif // MAKE_DLL
	#else
		#ifndef GOW_STATIC
			#define EXPORT __declspec(dllexport)
		#else
			#define EXPORT
		#endif
	#endif // MAKE_LIB

#endif
#include <GL/glew.h>

#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <list>
#include <vector>
#include <algorithm>
#include <exception>

#ifdef _WIN32
	#include <direct.h>
#endif // _WIN32

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

#include <SDL.h>
#include <SDL_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glm;

namespace GOW
{
	// Ӳ����Ϣ
	struct FDeviceInfo
	{
		// �豸ƽ̨��(Window, linux)
		std::string PlatformName;
		
		// CPU������
		int32 LogicalCoresNum;

		// �豸�ڴ��С(MB)
		int32 SystemRam;

		// ��ʾ�豸����
		int32 DisplaysNum;

		// ÿ����ʾ�豸��ʾ����
		std::vector<SDL_DisplayMode> DesktopDisplayModes;

		// ���ݵ���ʾ�����б�
		std::vector<SDL_DisplayMode> SupportedDisplayModes;

		// ��ʾ��Χ
		std::vector<SDL_Rect> DisplayBounds;

		// ��Ƭ����󶥵���
		int32 MaxPatchVertices;

		// ����ϸ�����ȼ�
		int32 MaxTessLevel;
	};

	// Class GOWEngine
	// ��ʼ��GOW�⣬�ṩ�豸��Ϣ
	class GOWEngine
	{
		static bool bInitialized;

		EXPORT GOWEngine();
		EXPORT ~GOWEngine();

	public:
		// ��ʼ��
		// �������true����ʼ���ɹ�������ʧ��
		EXPORT static bool Init();

		// ж��GOWEngine
		EXPORT static void Quit();

		// ��ʼ��GLEW
		// �������true����ʼ���ɹ�������ʧ��
		EXPORT static bool InitGlew();

		// ��ʼ��SDL2_img
		// �������true����ʼ���ɹ�������ʧ��
		EXPORT static bool InitImg();

		// ж��img
		EXPORT static void QuitImg();

		// ��ʼ��SDL2
		// �������true����ʼ���ɹ�������ʧ��
		EXPORT static bool InitSDL();

		// ж��SDL2
		EXPORT static void QuitSDL();

		// ����Opengl�汾
		// InMajor ���汾��
		// InMinor �ΰ汾��
		// �ڴ��ڴ���֮ǰ���ô˺���
		// �������İ汾��Ч��ʹ��Ĭ�ϰ汾��3.0
		EXPORT static void SetGLVersion(int32 InMajor, int32 InMinor);

		// ������Ⱥ�ģ�建��Ĵ�С
		// InDepthSize ��Ȼ����С����Сֵ
		// InStencilSize ģ�建���С����Сֵ
		// �ڴ��ڴ���֮ǰ���ô˺���
		EXPORT static void SetDepthStencilSize(int32 InDepthSize, int32 InStencilSize);

		// ���ö��ز����Ĳ�������
		// InNumberSamples ��������
		EXPORT static void SetMsaaSampleNumber(int32 InNumberSamples);

		// �Ƿ�֧������
		// �����true���Կ��������������false�����������
		EXPORT static void EnableScreensaver(bool InEnable);

		// �Ƿ���VSync(VSync��ֹ��Ⱦ����Ͽ�)
		// InOn true������false�ر�
		// �������false����ʾ����֧��VSync
		EXPORT static bool EnableVSync(bool InOn);

		// �����ڵĹ���Ŀ¼ӳ�䵽������ִ���ļ���Ŀ¼
		// InArgv ��main��������������в�������
		// ����ɹ�����true�����򷵻�false
		EXPORT static bool ChdirToBin(char** InArgv);

		// ��ȡ�������豸��Ϣ
		EXPORT static void GetDeviceInfo();

		// ���OpenGL������Ϣ
		// ��Ҫֱ�ӵ��ô˺���
		// ֱ��ʹ��CHECK_GL_ERROR
		EXPORT static void CheckError(std::string InMessage, std::string InFile, uint32 Inline);
	public:
		// �����True������SetGLVersion����
		EXPORT static bool bGLVersionManual;

		// �豸��Ϣ
		EXPORT static FDeviceInfo DeviceInfo;

		// �����ַ����б�
		EXPORT static std::vector<std::string> ErrorString;
	};
};

#endif