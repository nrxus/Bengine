#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Bengine {
	enum WindowFlags {INVISIBLE=0x1, FULLSCREEN=0x2, BORDERLESS=0x4};

	class Window {
	public:
		Window();
		~Window();
		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		int getScreenWidth() { return m_screenWidth; }
		int getScreenHeight() { return m_screenHeight; }
		void swapBuffer();

	private:
		int m_screenWidth;
		int m_screenHeight;
		SDL_Window* m_sdlWindow;
	};
}
