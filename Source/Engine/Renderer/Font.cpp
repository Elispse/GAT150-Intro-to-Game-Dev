#include "Font.h"
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

void Jackster::Font::Load(const std::string& fileName, int fontSize)
{
	m_ttfFont = TTF_OpenFont(fileName.c_str(), fontSize);
}
