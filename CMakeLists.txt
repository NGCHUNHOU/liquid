cmake_minimum_required(VERSION 3.0...4.0)
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
	if (NOT MINGW)
    message(":24 non MINGW environment is not supported")
		return()
	endif()

	if (MINGW)
		message("append_mingw_libcxx_to:29 platform detected is MinGW, searching for dll files for binary packaging...")

    get_filename_component(TOOLCHAIN_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    message(STATUS "append_mingw_libcxx_to:CMAKE_CXX_COMPILER:32: active C++ compiler ${CMAKE_CXX_COMPILER}")
    message(STATUS "append_mingw_libcxx_to:TOOLCHAIN_BIN_DIR:33: expecting runtime DLLs in ${TOOLCHAIN_BIN_DIR}")
    find_file(LIBCXX_RUNTIME_DLL
      NAMES libc++.dll
      PATHS "${TOOLCHAIN_BIN_DIR}"
      NO_DEFAULT_PATH   # don't let CMake fall back to unrelated system paths
    )
    find_file(LIBUNWIND_RUNTIME_DLL
      NAMES libunwind.dll
      PATHS "${TOOLCHAIN_BIN_DIR}"
      NO_DEFAULT_PATH
    )

    if (NOT LIBCXX_RUNTIME_DLL OR NOT LIBUNWIND_RUNTIME_DLL)
      message(FATAL_ERROR
        "append_mingw_libcxx_to:47"
        "libc++.dll / libunwind.dll not found next to the active compiler "
        "(${TOOLCHAIN_BIN_DIR}). This target expects an llvm-mingw-style "
        "toolchain that ships its runtime DLLs alongside clang++.exe. "
        "dlls copy aborted.")
    endif()

    message(STATUS "append_mingw_libcxx_to:LIBCXX_RUNTIME_DLL,LIBUNWIND_RUNTIME_DLL,destdir:54 copying ${LIBCXX_RUNTIME_DLL} and ${LIBUNWIND_RUNTIME_DLL} -> ${destdir}")
    file(COPY ${LIBCXX_RUNTIME_DLL} ${LIBUNWIND_RUNTIME_DLL} DESTINATION ${destdir})
	endif()
endfunction()

append_mingw_libcxx_to(${CMAKE_BINARY_DIR}/bin)
