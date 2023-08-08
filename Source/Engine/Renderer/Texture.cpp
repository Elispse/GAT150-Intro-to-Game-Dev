#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL2-2.28.1/include/SDL_image.h>

namespace Jackster
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Load(std::string& filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			WARNING_LOG("Could not create surface: " << filename);
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			WARNING_LOG("");
			return false;
		}
		return true;
	}

	vec2 Texture::GetSize()
	{
		// ASSERT texture is not null
		SDL_Point point;

		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
		SDL_QueryTexture(m_texture, NULL, NULL, &point.x, &point.y);

		return vec2{ point.x, point.y };
	}

	bool Texture::Create(std::string filename, ...)
	{
		// va_list - type to hold information about variable arguments
		va_list args;

		// va_start - enables access to variadic function arguments
		va_start(args, filename);

		// va_arg - accesses the next variadic function arguments
		Renderer& renderer = va_arg(args, Renderer);

		// va_end - ends traversal of the variadic function arguments
		va_end(args);


		return Load(filename, renderer);
	}

}