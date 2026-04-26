file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(game_level ${SOURCES} ${HEADERS})
target_include_directories(game_level PUBLIC include)
target_link_libraries(game_level PUBLIC glad glm-header-only game_object sprite_renderer resource_manager)
