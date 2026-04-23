file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(sprite_renderer ${SOURCES} ${HEADERS})
target_include_directories(sprite_renderer PUBLIC include)
target_link_libraries(sprite_renderer PUBLIC glad texture shader)