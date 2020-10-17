# Specify properties and create project
cmake_minimum_required(VERSION 3.7)
project(sumo)

# Compile additional files as seprate libraries to link
add_library(entities STATIC src/entities/entity.cpp src/entities/player.cpp src/entities/blob.cpp src/entities/big_blob.cpp)
add_library(vec2d STATIC src/util/vec2d.cpp)

# Attempt to find SDL libraries
find_package(SDL2 REQUIRED)

# Specify include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Create executable and set properties
add_executable(sumo src/sumo_game.cpp)
set_target_properties(sumo PROPERTIES CXX_STANDARD_REQUIRED YES CCXX_EXTENSIONS NO)

# Link to created libraries and to SDL
target_link_libraries(sumo entities vec2d)
target_link_libraries(sumo ${SDL2_LIBRARIES} SDL2_image SDL2_gfx)

# Tests handled in seperate cmake
add_subdirectory(tests)
enable_testing()
add_test(NAME testVector2d COMMAND runTestVector2d)

# Copy art assets into build directory
file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})