#pragma once
#include <string>
#include <SDL2-2.28.1/include/SDL.h>

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

	friend class Text;

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer{ nullptr };
		SDL_Window* m_window{ nullptr };
	};

	extern Renderer g_renderer;

}