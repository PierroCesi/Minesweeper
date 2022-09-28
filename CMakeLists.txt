cmake_minimum_required(VERSION 3.21)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(minesweeper main.cpp View/View.cpp View/View.h Model/Map.cpp Model/Map.h Controller/MainController.cpp Controller/MainController.h Model/Tile.cpp Model/Tile.h Model/Scoreboard.cpp Model/Scoreboard.h)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio sfml-network)