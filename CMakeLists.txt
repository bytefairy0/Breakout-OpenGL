cmake_minimum_required(VERSION 3.22.1)
project(OpenGLgame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 3.4 REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_executable(OpenGLgame ${SOURCES})
target_include_directories(OpenGLgame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(OpenGLgame PRIVATE glfw ${CMAKE_DL_LIBS})

find_package(OpenGL REQUIRED)
target_link_libraries(OpenGLgame PRIVATE OpenGL::GL)

message("Source directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message("Build directory:  ${CMAKE_BINARY_DIR}")
