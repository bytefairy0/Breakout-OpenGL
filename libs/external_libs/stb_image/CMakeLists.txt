file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(stb_image ${SOURCES} ${HEADERS})
target_include_directories(stb_image PUBLIC include)