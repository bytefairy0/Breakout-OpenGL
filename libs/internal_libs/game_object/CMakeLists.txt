file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(game_object ${SOURCES} ${HEADERS})
target_include_directories(game_object PUBLIC include)
target_link_libraries(game_object PUBLIC glad glm-header-only sprite_renderer texture)
