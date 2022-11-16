cmake_minimum_required(VERSION 3.0)
project(liquid)
# include_directories(${PROJECT_SOURCE_DIR}/installed/x64-windows/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# print all variables into variable log file "./build/compileVars.log"
if (EXISTS "${PROJECT_SOURCE_DIR}/build/compileVars.log")
	message(STATUS "detected existing compileVars.log, remove and update it")
	execute_process(COMMAND bash -c "rm ${PROJECT_SOURCE_DIR}/build/compileVars.log")
endif()

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
	file(APPEND ${PROJECT_SOURCE_DIR}/build/compileVars.log "${_variableName}=${${_variableName}}\n")
endforeach()

add_executable(liquid src/main.cpp src/argparser.cpp)
target_link_libraries(liquid PRIVATE fmt::fmt sfml-system sfml-network sfml-graphics sfml-window)
