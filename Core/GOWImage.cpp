#include "GOWImage.h"

using namespace GOW;

std::vector<std::string> GOWImage::Paths = { "./" };

GOWImage::GOWImage()
{
	FreeData = false;
	Image = nullptr;
	Width = 0;
	Height = 0;
	BytesPerPixel = 0;
	Data = nullptr;
}

GOWImage::GOWImage(std::string InFileName)
{
	FreeData = false;
	Image = nullptr;
	Width = 0;
	Height = 0;
	BytesPerPixel = 0;
	Data = nullptr;

	if (!Load(InFileName))
	{
		std::string Error = std::string("Error loading image: ") + SDL_GetError();
		GOWEngine::ErrorString.push_back(Error);
		throw std::runtime_error(Error);
	}
}

GOWImage::GOWImage(uint32 InWidth, uint32 InHeight, uint32 InBytesPerPixel)
{
	FreeData = false;
	Image = nullptr;
	Width = 0;
	Height = 0;
	BytesPerPixel = 0;
	Data = nullptr;

	if (!Load(Width, Height, BytesPerPixel, Data))
	{
		std::string Error = std::string("Error loading image: ") + SDL_GetError();

		GOWEngine.ErrorString.push_back(Error);
		throw std::runtime_error(Error);
	}
}

GOWImage::~GOWImage()
{
	SDL_FreeSurface(Image);

	if (FreeData)
		free(Data);
}

bool GOWImage::CreateEmpty(uint32 InWidth, uint32 InHeight)
{
	if (Image)
	{
		SDL_FreeSurface(Image);

		if (FreeData)
			free(Data);

		Image = nullptr;
	}

	Width = InWidth;
	Height = InHeight;
	BytesPerPixel = 4;

	uint32 RMask, GMask, BMask, AMask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	RMask = 0xff000000;
	GMask = 0x00ff0000;
	BMask = 0x0000ff00;
	AMask = 0x000000ff;
#else
	RMask = 0x000000ff;
	GMask = 0x0000ff00;
	BMask = 0x00ff0000;
	AMask = 0xff000000;
#endif

	Image = SDL_CreateRGBSurface(0, Width, Height, 32, RMask, GMask, BMask, AMask);
	if (!Image)
	{
		GOWEngine::ErrorString.push_back(std::string("Unable to create an empty image: ") + SDL_GetError());

		Width = 0;
		Height = 0;
		BytesPerPixel = 0;
		Data = nullptr;
		return false;
	}

	Data = Image->pixels;
	return true;
}

bool GOWImage::Load(const std::string& InFileName)
{
	if (Image)
	{
		SDL_FreeSurface(Image);
		if (FreeData)
			free(Data);
	}

	if ((InFileName.length() > 1 && InFileName[0] == '/') ||
		(InFileName.length() > 2 && InFileName[1] == ':'))
	{
		// 绝对路径
		Image = IMG_Load(InFileName.c_str());
	}
	else
	{
		// 相对路径
		for (uint32 i = 0; i < Paths.size(); i++)
		{
			Image = IMG_Load((Paths[i] + InFileName).c_str());
			if(Image)
				break;
		}
	}

	if (!Image)
	{
		GOWEngine::ErrorString.push_back(std::string("Unable to load image: ") + 
										InFileName + std::string(" - ") + 
										IMG_GetError());

		Width = 0;
		Height = 0;
		BytesPerPixel = 0;
		Data = nullptr;
		return false;
	}

	Width = Image->w;
	Height = Image->h;
	BytesPerPixel = Image->format->BytesPerPixel;
	Data = Image->pixels;

	return true;
}

bool GOWImage::Load(uint32 InWidth, uint32 InHeight, uint32 InBytesPerPixel, void* InData)
{
	if (Image)
	{
		SDL_FreeSurface(Image);
		if (FreeData)
			free(Data);

		Image = nullptr;
	}

	uint32 RMask, GMask, BMask, AMask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	RMask = 0xff000000;
	GMask = 0x00ff0000;
	BMask = 0x0000ff00;
	AMask = 0x000000ff;
#else
	RMask = 0x000000ff;
	GMask = 0x0000ff00;
	BMask = 0x00ff0000;
	AMask = 0xff000000;
#endif

	Width = InWidth;
	Height = InHeight;
	BytesPerPixel = InBytesPerPixel;
	Data = malloc(Width * Height * BytesPerPixel);

	if (!Data)
	{
		GOWEngine::ErrorString.push_back(std::string("Image - load: Unable to allocate memory"));

		Width = 0;
		Height = 0;
		BytesPerPixel = 0;
		return false;
	}

	memcpy(Data, InData, Width * Height * BytesPerPixel);
	FreeData = true;

	Image = SDL_CreateRGBSurfaceFrom(Data, Width, Height, 8 * BytesPerPixel, 
									BytesPerPixel * Width, RMask, GMask, BMask, AMask);

	if (!Image)
	{
		GOWEngine::ErrorString.push_back(std::string("Unable to load the image from buffer: ") + SDL_GetError());

		Width = 0;
		Height = 0;
		BytesPerPixel = 0;
		Data = nullptr;
		return false;
	}

	return true;
}

bool GOWImage::Save(const std::string& InFileName)
{
	int32 Ret = SDL_SaveBMP(Image, InFileName.c_str());

	if (Ret < 0)
	{
		GOWEngine::ErrorString.push_back(std::string("Unable to save the image to ") + 
										InFileName + std::string(": ") + SDL_GetError());
		return false;
	}

	return true;
}

bool GOWImage::CopyFrom(const GOWImage& InSrc, int32 InX, int32 InY)
{
	SDL_Rect Rect;
	Rect.x = InX;
	Rect.y = InY;

	return CopyFrom(InSrc, Rect);
}

bool GOWImage::CopyFrom(const GOWImage& InSrc, SDL_Rect& InDstRect)
{
	if (!Image)
	{
		Image = SDL_ConvertSurface(InSrc.Image, InSrc.Image->format, InSrc.Image->flags);

		if (!Image)
		{
			GOWEngine::ErrorString.push_back(std::string("SDL_ConverSurface failed: ") + SDL_GetError());
			return false;
		}
	}

	if (SDL_BlitSurface(InSrc.Image, nullptr, Image, &InDstRect) < 0)
	{
		GOWEngine::ErrorString.push_back(std::string("SDL_BlitSurface failed: ") + SDL_GetError());
		return false;
	}

	return true;
}

bool GOWImage::CopyFrom(const GOWImage& InSrc, SDL_Rect& InDstRect, const SDL_Rect& InSrcRect)
{
	if (!Image)
	{
		Image = SDL_ConvertSurface(InSrc.Image, InSrc.Image->format, InSrc.Image->flags);

		if (!Image)
		{
			GOWEngine::ErrorString.push_back(std::string("SDL_ConvertSurface failed: ") + SDL_GetError());

			return false;
		}

		if (SDL_BlitSurface(InSrc.Image, &InSrcRect, Image, &InDstRect) < 0)
		{
			GOWEngine::ErrorString.push_back(std::string("SDL_BlitSurface failed: ") + SDL_GetError());
			return false;
		}

		return true;
	}
}

void GOWImage::VerticalFlip()
{
	if (!Image)
		return;

	uint32 Bpp = Image->format->BytesPerPixel;
	std::unique_ptr<unsigned char[]> Buffer = std::make_unique<unsigned char[]>(Width * Height * Bpp);

	for(uint32 y = 0; y < Height; y++)
		for(uint32 x = 0; x < Width; x++)
			for (uint32 c = 0; c < Bpp; c++)
			{
				Buffer[(y * Width + x) * Bpp + c] = ((unsigned char*)Image->pixels)[((Height - y - 1) * Width + x) * Bpp + c];
			}

	memcpy(Image->pixels, Buffer.get(), Width * Height * Bpp);
}

void GOWImage::HorizontalFlip()
{
	if (!Image)
		return;

	uint32 Bpp = Image->format->BytesPerPixel;

	std::unique_ptr<unsigned char[]> Buffer = std::make_unique<unsigned char[]>(Width * Height * Bpp);

	for(uint32 y = 0; y < Height; y++)
		for(uint32 x = 0; x < Width; x++)
			for (uint32 c = 0; c < Bpp; c++)
			{
				Buffer[(y * Width + x) * Bpp + c] = ((unsigned char*)Image->pixels)[((Height - x - 1) * Width + x) * Bpp + c];
			}

	memcpy(Image->pixels, Buffer.get(), Width * Height * Bpp);
}

void GOWImage::AddPath(std::string InPath)
{
	if (InPath[InPath.length() - 1] != '/')
		InPath += '/';

	if (std::find(Paths.begin(), Paths.end(), InPath) == Paths.end())
		Paths.push_back(InPath);
}