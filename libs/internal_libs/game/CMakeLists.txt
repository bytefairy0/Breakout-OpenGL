file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(game ${SOURCES} ${HEADERS})
target_include_directories(game PUBLIC include)
target_link_libraries(game PUBLIC glad glfw 
                    resource_manager sprite_renderer game_level
                    ball particle_generator)