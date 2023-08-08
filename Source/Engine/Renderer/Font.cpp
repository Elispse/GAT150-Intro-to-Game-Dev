#include "Font.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include <SDL2-2.28.1/include/SDL_ttf.h>

Jackster::Font::Font(const std::string& fileName, int fontSize)
{
	Load(fileName, fontSize);
}

Jackster::Font::~Font()
{
	if (m_ttfFont != NULL)
	{
		TTF_CloseFont(m_ttfFont);
	}
}

bool Jackster::Font::Create(std::string filename, ...)
{
	va_list args;

	va_start(args, filename);

	int fontSize = va_arg(args, int);

	va_end(args);

	return Load(filename, fontSize);
}

bool Jackster::Font::Load(const std::string& fileName, int fontSize)
{
	m_ttfFont = TTF_OpenFont(fileName.c_str(), fontSize);
	if (m_ttfFont = nullptr)
	{
		WARNING_LOG("failed to open font:" << fileName);
		return false;
	}
	return true;
}

