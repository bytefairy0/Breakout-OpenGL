file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(shader ${SOURCES} ${HEADERS})
target_include_directories(shader PUBLIC include)
target_link_libraries(shader PUBLIC glad glfw glm-header-only)