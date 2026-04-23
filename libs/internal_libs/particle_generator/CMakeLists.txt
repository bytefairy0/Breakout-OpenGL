file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(particle_generator ${SOURCES} ${HEADERS})
target_include_directories(particle_generator PUBLIC include)
target_link_libraries(particle_generator game_object)