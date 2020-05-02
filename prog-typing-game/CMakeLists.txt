cmake_minimum_required (VERSION 2.6)

project (prog-typing-game)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(prog-typing-game
	main.cc
	Window.cc
	GameWindow.cc
	ResourceManager.cc
	)
	
target_link_libraries(prog-typing-game ${SDL2_LIBRARIES})
