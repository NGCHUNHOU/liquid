cmake_minimum_required(VERSION 3.0)
project(liquid)
# set(DCMAKE_TOOLCHAIN_FILE "C:\\Users\\knxuser\\Desktop\\vcpkg\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
# include("C:\\Users\\knxuser\\Desktop\\vcpkg\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
# include_directories(${PROJECT_SOURCE_DIR}/src)
# set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/installed/x64-windows/share/fmt")
# set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/installed/x64-windows/share/sfml")

# include_directories(${PROJECT_SOURCE_DIR}/installed/x64-windows/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
add_executable(liquid src/main.cpp src/argparser.cpp)
target_link_libraries(liquid PRIVATE fmt::fmt sfml-system sfml-network sfml-graphics sfml-window)

# target_link_libraries(app PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# If you want SFML to provide an implementation of main():
# target_link_libraries(main PRIVATE sfml-main)
