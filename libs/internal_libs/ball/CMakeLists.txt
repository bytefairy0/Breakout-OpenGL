file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(ball_object ${SOURCES} ${HEADERS})
target_include_directories(ball_object PUBLIC include)
target_link_libraries(ball_object PUBLIC glad glm texture game_object)