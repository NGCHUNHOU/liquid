cmake_minimum_required(VERSION 3.0)
project(liquid)
# include_directories(${PROJECT_SOURCE_DIR}/installed/x64-windows/include)
# include_directories(${PROJECT_SOURCE_DIR}/include)
# find_package(fmt CONFIG REQUIRED)
# find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_subdirectory(SFML)
set(SOURCE_FILES 
	src/main.cpp 
	src/argparser.cpp 
	src/imageHandler.cpp
)

add_executable(liquid ${SOURCE_FILES})
target_include_directories(liquid PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(liquid PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
