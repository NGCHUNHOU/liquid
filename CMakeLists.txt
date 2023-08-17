cmake_minimum_required(VERSION 3.0)
project(liquid)
# include_directories(${PROJECT_SOURCE_DIR}/installed/x64-windows/include)
# include_directories(${PROJECT_SOURCE_DIR}/include)
# find_package(fmt CONFIG REQUIRED)
# find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES 
	src/main.cpp 
	src/argparser.cpp 
	src/imageHandler.cpp
)

add_executable(liquid ${SOURCE_FILES})
add_subdirectory(SFML)
target_link_libraries(liquid sfml-system sfml-network sfml-graphics sfml-window)

function(append_mingw_libcxx_to destdir)
	if (MINGW)
		message("platform detected is MinGW, searching for dll files for binary packaging...")
		find_library(LIBCXX_DLL c++ PATHS ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
		find_library(LIBUNWIND_DLL unwind PATHS ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
		if(NOT LIBCXX_DLL OR NOT LIBUNWIND_DLL)
			message(FATAL_ERROR "libc++.dll.a or libunwind.dll.a not found. dlls copy aborted")
		endif()
		get_filename_component(LIBCXX_DLL_PARENT_DIR ${LIBCXX_DLL} DIRECTORY)
		get_filename_component(LIBCXX_DLL_GRAND_PARENT_DIR ${LIBCXX_DLL_PARENT_DIR} DIRECTORY)
		set(LIBCXXDLLFILES_DIR ${LIBCXX_DLL_GRAND_PARENT_DIR}/bin)
		if (NOT EXISTS "${LIBCXXDLLFILES_DIR}/libc++.dll" OR NOT EXISTS "${LIBCXXDLLFILES_DIR}/libunwind.dll")
			message(FATAL_ERROR "libc++.dll or libunwind.dll not found. dlls copy aborted")
		endif()
		set(LIBCXXDLLFILES ${LIBCXXDLLFILES_DIR}/libc++.dll ${LIBCXXDLLFILES_DIR}/libunwind.dll)
		message("copying ${LIBCXXDLLFILES} from ${LIBCXXDLLFILES_DIR} to ${CMAKE_BINARY_DIR}/bin")
		file(COPY ${LIBCXXDLLFILES} DESTINATION ${destdir})
	endif()
endfunction()

append_mingw_libcxx_to(${CMAKE_BINARY_DIR}/bin)
