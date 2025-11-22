cmake_minimum_required(VERSION 3.28)
project(Match3Game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")

add_executable(Match3Game ${SOURCES})
target_include_directories(Match3Game PRIVATE include)
target_compile_features(Match3Game PRIVATE cxx_std_17)
target_link_libraries(Match3Game PRIVATE SFML::Graphics)