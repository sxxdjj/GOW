#pragma once
#ifndef __GOWENGINE_H__
#define __GOWENGINE_H__

// 打印OpenGL错误信息和使用此宏的相关文件名及相应的行数
#define CHEK_GL_ERROR(message) do{\
	GOW::GOWEngine::CheckError(message, __FILE__, __LINE__);\
}while(0)

#ifdef _WIN32
	#ifdef MAKE_LIB // 构建GOW
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
	// 硬件信息
	struct FDeviceInfo
	{
		// 设备平台名(Window, linux)
		std::string PlatformName;
		
		// CPU核数量
		int32 LogicalCoresNum;

		// 设备内存大小(MB)
		int32 SystemRam;

		// 显示设备数量
		int32 DisplaysNum;

		// 每个显示设备显示类型
		std::vector<SDL_DisplayMode> DesktopDisplayModes;

		// 兼容的显示类型列表
		std::vector<SDL_DisplayMode> SupportedDisplayModes;

		// 显示范围
		std::vector<SDL_Rect> DisplayBounds;

		// 面片的最大顶点数
		int32 MaxPatchVertices;

		// 曲面细分最大等级
		int32 MaxTessLevel;
	};

	// Class GOWEngine
	// 初始化GOW库，提供设备信息
	class GOWEngine
	{
		static bool bInitialized;

		EXPORT GOWEngine();
		EXPORT ~GOWEngine();

	public:
		// 初始化
		// 如果返回true，初始化成功，否则失败
		EXPORT static bool Init();

		// 卸载GOWEngine
		EXPORT static void Quit();

		// 初始化GLEW
		// 如果返回true，初始化成功，否则失败
		EXPORT static bool InitGlew();

		// 初始化SDL2_img
		// 如果返回true，初始化成功，否则失败
		EXPORT static bool InitImg();

		// 卸载img
		EXPORT static void QuitImg();

		// 初始化SDL2
		// 如果返回true，初始化成功，否则失败
		EXPORT static bool InitSDL();

		// 卸载SDL2
		EXPORT static void QuitSDL();

		// 设置Opengl版本
		// InMajor 主版本号
		// InMinor 次版本号
		// 在窗口创建之前调用此函数
		// 如果传入的版本无效，使用默认版本号3.0
		EXPORT static void SetGLVersion(int32 InMajor, int32 InMinor);

		// 设置深度和模板缓冲的大小
		// InDepthSize 深度缓冲大小的最小值
		// InStencilSize 模板缓冲大小的最小值
		// 在窗口创建之前调用此函数
		EXPORT static void SetDepthStencilSize(int32 InDepthSize, int32 InStencilSize);

		// 设置多重采样的采样个数
		// InNumberSamples 采样个数
		EXPORT static void SetMsaaSampleNumber(int32 InNumberSamples);

		// 是否支持屏保
		// 如果是true可以开启屏保，如果是false不会出现屏保
		EXPORT static void EnableScreensaver(bool InEnable);

		// 是否开启VSync(VSync防止渲染画面断开)
		// InOn true开启，false关闭
		// 如果返回false，显示器不支持VSync
		EXPORT static bool EnableVSync(bool InOn);

		// 把现在的工作目录映射到包含可执行文件的目录
		// InArgv 从main函数传入的命令行参数数组
		// 如果成功返回true，否则返回false
		EXPORT static bool ChdirToBin(char** InArgv);

		// 获取和设置设备信息
		EXPORT static void GetDeviceInfo();

		// 输出OpenGL错误信息
		// 不要直接调用此函数
		// 直接使用CHECK_GL_ERROR
		EXPORT static void CheckError(std::string InMessage, std::string InFile, uint32 Inline);
	public:
		// 如果是True，调用SetGLVersion函数
		EXPORT static bool bGLVersionManual;

		// 设备信息
		EXPORT static FDeviceInfo DeviceInfo;

		// 错误字符串列表
		EXPORT static std::vector<std::string> ErrorString;
	};
};

#endif