cmake_minimum_required(VERSION 3.10)
project(BreakoutGame)

set(CMAKE_CXX_STANDARD 17)

# Use pkg-config to find SDL2 and add-ons
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# Find OpenGL (required for GLAD and rendering)
find_package(OpenGL REQUIRED)

# Include directories
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}    # OpenGL headers
    include  
)

# Link directories
link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_IMAGE_LIBRARY_DIRS}
    ${SDL2_MIXER_LIBRARY_DIRS}
    ${SDL2_TTF_LIBRARY_DIRS}
)

# Extra compiler flags if needed
add_definitions(
    ${SDL2_CFLAGS_OTHER}
    ${SDL2_IMAGE_CFLAGS_OTHER}
    ${SDL2_MIXER_CFLAGS_OTHER}
    ${SDL2_TTF_CFLAGS_OTHER}
)

# Source files
file(GLOB SOURCES "src/*.cpp" "src/*.c" "src/source/*.cpp" "res/shaders/*.cpp" "src/vendor/stb_image/*.cpp")

# Executable
add_executable(Breakout ${SOURCES})

# Link libraries
target_link_libraries(Breakout
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
