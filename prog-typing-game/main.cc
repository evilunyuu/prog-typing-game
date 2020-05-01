#include <iostream>
#include <stdexcept>
#include <memory>

#include <SDL2/SDL.h>

class Window
{
public:
	static constexpr int DEFAULT_WIDTH = 1280;
	static constexpr int DEFAULT_HEIGHT = 800;
protected:
	std::shared_ptr<SDL_Window> _window { nullptr };
	int _width { 0 };
	int _height { 0 };

public:
	[[deprecated("Don't call this constructor directly!")]]
	Window(int width, int height);
	virtual ~Window() = default;

	static std::shared_ptr<Window> create(
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT);
};

Window::Window(int width, int height):
		_width(width), _height(height)
{
	_window = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
					"prog-typing-game",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width, height,
					SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (_window == nullptr)
		throw std::runtime_error("SDL_CreateWindow failed!");
}

std::shared_ptr<Window> Window::create(int width, int height)
{
	return std::make_shared<Window>(width, height);
}


int main(int argc, char **argv)
{
	try {
		// Инициализация SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw std::runtime_error("SDL_Init() failed!");

		// Создание окна
		auto win = Window::create();



		// Эту задержку потом удалим
		SDL_Delay(2000);

	} catch (const std::exception& e) {
		std::cout <<
				"An exception has occured:" << std::endl <<
				e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cout <<
				"An unknown exception has occured!" << std::endl;
		return 2;
	}

	return 0;
}
