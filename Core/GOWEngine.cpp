#include "GOWEngine.h"

using namespace GOW;

bool GOWEngine::bGLVersionManual = false;
bool GOWEngine::bInitialized = false;
FDeviceInfo GOWEngine::DeviceInfo;
std::vector<std::string> GOWEngine::ErrorString;

bool GOWEngine::InitGlew()
{
	glewExperimental = GL_TRUE;

	if (glewInit())
	{
		GOWEngine::ErrorString.push_back("glewInit failed");
		return false;
	}

	return true;
}

bool GOWEngine::InitImg()
{
	uint32 Flags = IMG_INIT_JPG | IMG_INIT_PNG;

	if ((IMG_Init(Flags) & Flags) != Flags)
	{
		GOWEngine::ErrorString.push_back(std::string("IMG_Init Error: ") + SDL_GetError());
		return false;
	}

	return true;
}

void GOWEngine::QuitImg()
{
	IMG_Quit();
}

bool GOWEngine::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER))
	{
		GOWEngine::ErrorString.push_back(std::string("SDL_Init Error: ") + SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	return true;
}

void GOWEngine::QuitSDL()
{
	SDL_Quit();
}

bool GOWEngine::Init()
{
	if (GOWEngine::bInitialized)
		return true;

	if (GOWEngine::InitSDL() && GOWEngine::InitImg())
	{
		GOWEngine::bInitialized = true;
		GOWEngine::GetDeviceInfo();

		return true;
	}

	GOWEngine::Quit();
	return false;
}

void GOWEngine::SetGLVersion(int32 InMajor, int32 InMinor)
{
	int32 Major = 3;
	int32 Minor = 0;

	if (InMajor == 3)
	{
		if (InMinor < 0 || InMinor > 3)
		{
			GOWEngine::ErrorString.push_back("Unsupported version number. Defaulting to version 3.0");
		}
		else
		{
			Major = InMajor;
			Minor = InMinor;
		}
	}
	else if (InMajor == 4)
	{
		if (InMinor < 0 || InMinor > 6)
		{
			GOWEngine::ErrorString.push_back("Unsupported version number. Defaulting to version 3.0");
		}
		else
		{
			Major = InMajor;
			Minor = InMinor;
		}
	}
	else
	{
		GOWEngine::ErrorString.push_back("Unsupported version number. Defaulting to version 3.0");
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	GOWEngine::bGLVersionManual = true;
}

void GOWEngine::SetDepthStencilSize(int32 InDepthSize, int32 InStencilSize)
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, InDepthSize);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, InStencilSize);
}

void GOWEngine::SetMsaaSampleNumber(int32 InNumberSamples)
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, InNumberSamples);
}

void GOWEngine::Quit()
{
	GOWEngine::bInitialized = false;
	GOWEngine::bGLVersionManual = false;
	GOWEngine::QuitImg();
	GOWEngine::QuitSDL();
}

void GOWEngine::EnableScreensaver(bool InEnable)
{
	if (InEnable)
		SDL_EnableScreenSaver();
	else
		SDL_DisableScreenSaver();
}

bool GOWEngine::EnableVSync(bool InOn)
{
	int32 Ret;
	if (InOn)
	{
		Ret = SDL_GL_SetSwapInterval(-1);

		if (!Ret)
		{
			Ret = SDL_GL_SetSwapInterval(1);
		}
	}
	else
	{
		Ret = SDL_GL_SetSwapInterval(0);
	}

	return (Ret == 1);
}

bool GOWEngine::ChdirToBin(char** InArgv)
{
	std::string Path(InArgv[0]);

	Path = Path.substr(0, Path.find_last_of("\\/"));

	int32 Ret = _chdir(Path.c_str());

	if (Ret)
	{
		std::string Error("An error occured while trying to change "
						"current working directory to the directory containing "
						"the executable file.");
		GOWEngine::ErrorString.push_back(Error);
		return false;
	}

	return true;
}

void GOWEngine::CheckError(std::string InMessage, std::string InFile, uint32 Inline)
{
	std::string ErrString;

	GLenum GLError = GL_NO_ERROR;

	do
	{
		GLError = glGetError();
		switch (GLError)
		{
		case GL_INVALID_ENUM:
			ErrString = "INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			ErrString = "INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			ErrString = "INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			ErrString = "INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			ErrString = "OUT_OF_MEMORY";
			break;
		case GL_STACK_OVERFLOW:
			ErrString = "STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			ErrString = "STACK_UNDERFLOW";
			break;
		default:
			return;
		}

		std::cerr << InFile << " - " << Inline << ": " << ErrString << " - " << InMessage << std::endl;
	} while (GLError != GL_NO_ERROR);
}

void GOWEngine::GetDeviceInfo()
{
	GOWEngine::DeviceInfo.PlatformName = std::string(SDL_GetPlatform());
	GOWEngine::DeviceInfo.LogicalCoresNum = SDL_GetCPUCount();
}