file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(resource_manager ${SOURCES} ${HEADERS})
target_include_directories(resource_manager PUBLIC include)
target_link_libraries(resource_manager PUBLIC glad texture shader stb_image)