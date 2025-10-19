cmake_minimum_required(VERSION 3.13)
project(Breakout LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES "Breakout/*.cpp")
add_executable(${PROJECT_NAME}
	${SRC_FILES}
)

add_subdirectory(third_party/sfml)
target_include_directories(${PROJECT_NAME} PRIVATE third_party/sfml/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
