#pragma once
#include "Font.h"
#include "Core/Math/Color.h"
#include <string>
#include <memory>


struct SDL_Texture;

namespace Jackster
{
	class Renderer;
	class Text
	{
	public:
		Text() = default;
		Text(std::shared_ptr<Jackster::Font> font) : m_font{ font } {};
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);
		void Draw(Renderer& renderer, const class Transform& transform);

	private:
		std::shared_ptr<Jackster::Font> m_font;
		SDL_Texture* m_texture = nullptr;
	};
}