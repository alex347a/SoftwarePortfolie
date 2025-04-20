cmake_minimum_required(VERSION 3.10)
project(HeroGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(HeroGame
    src/main.cpp
    src/Karakter.cpp
    src/Hero.cpp
    src/Fjende.cpp
)

