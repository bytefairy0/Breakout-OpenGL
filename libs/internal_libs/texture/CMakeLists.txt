file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(texture ${SOURCES} ${HEADERS})
target_include_directories(texture PUBLIC include)
target_link_libraries(texture PUBLIC glad)