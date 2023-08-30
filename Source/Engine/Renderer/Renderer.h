#pragma once
#include <string>
#include <SDL2-2.28.1/include/SDL.h>
#include <Core/Math/Transform.h>


namespace Jackster {

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		bool Shutdown();
		
		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		void setColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawLine(float x1, float y1, float x2, float y2);
		void drawPoint(int x, int y);
		void drawPoint(float x, float y);

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);
		void DrawTexture(class Texture* texture, const Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform, const vec2& origin, bool flipH);

		SDL_Renderer* m_renderer = nullptr;

		friend class Text;
		friend class Texture;

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Window* m_window = nullptr;
	};

	extern Renderer g_renderer;

}