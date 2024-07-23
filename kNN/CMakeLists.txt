
project(Graph)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 20)

add_executable(GraphGenerator Graph.cpp GraphGenerator.cpp)
add_executable(test test.cpp Graph.cpp)
