cmake_minimum_required(VERSION 3.10)
project(HeroGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

# Compiler warnings configuration
if(MSVC)
    add_compile_options(/W4 /WX /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    add_compile_options(-Wconversion -Wsign-conversion)
endif()


include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(HeroGame ${SOURCES})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(HeroGame PRIVATE -Weverything)
endif()

target_compile_definitions(HeroGame PRIVATE 
    $<$<CONFIG:DEBUG>:DEBUG=1>
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(HeroGame PRIVATE -g3)
    endif()
endif()

target_link_libraries(HeroGame PRIVATE SQLite::SQLite3)
